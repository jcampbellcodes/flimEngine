#pragma once
#pragma once
#ifndef Collidable_H
#define Collidable_H

#include "err.h"
#include "AzulCore.h"
#include "RegState.h"
#include <list>

#include "CollisionDeregistrationCommand.h"
#include "CollisionRegistrationCommand.h"

#include "CollisionVolumeBSphere.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \enum	VolumeType
/// \ingroup COLLISIONS
/// \brief	Values that represent volume types.
////////////////////////////////////////////////////////////////////////////////////////////////////

enum class CollisionVolumeType
{
	BSPHERE,
	AABB,
	OBB,
	OCCLUSION_LINE
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	Collidable
///
/// \brief	A collidable.
///
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class Collidable
{
private:

	template<typename C> friend class CollisionRegistrationCommand;
	template<typename C> friend class CollisionDeregistrationCommand;
	template<typename C1, typename C2> friend class CollisionTestPairCommand;
	template<typename C> friend class CollisionTestSelfCommand;

	RegistrationState regState;

	SceneRegistrationCommand* regCommand;
	SceneDeregistrationCommand* deregCommand;

	CollisionVolume* collVolume;
	CollisionVolumeBSphere* defaultBS;

	Model* pColModel;

	std::list<Collidable*>::iterator deleteIter;

	bool colliding;

public:
	Collidable();
	virtual ~Collidable();
	Collidable(const Collidable&) = delete;
	const Collidable& operator= (const Collidable&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Collidable::Collision(Collidable*)
	///
	/// \brief	Collision callback
	/// \ingroup COLLISIONCALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	parameter1	Write behavior for a collision here
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode Collision(Collidable*) 
	{ 
		//DebugMsg::out("Collidable collision callback");
		return errcode::success; 
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Collidable::CollisionEnter(Collidable*)
	///
	/// \brief	Collision enter.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup COLLISIONCALLBACKS
	/// \param [in,out]	parameter1	If non-null, the first parameter.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode CollisionEnter(Collidable*)
	{
		//DebugMsg::out("Collidable collision callback");
		return errcode::success;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Collidable::CollisionExit()
	///
	/// \brief	Collision exit.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup COLLISIONCALLBACKS
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode CollisionExit()
	{
		//DebugMsg::out("Collidable collision callback");
		return errcode::success;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Collidable::CollisionTerrain(const CollisionVolumeAABB& )
	///
	/// \brief	Collision terrain.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup COLLISIONCALLBACKS
	/// \param	parameter1	The first parameter.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode CollisionTerrain(const CollisionVolumeAABB& )
	{
		return errcode::success;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	template <typename C> errcode Collidable::SubmitCollisionRegistration(C*c);
	///
	/// \brief	Submit collision registration of your type.
	///\ingroup COLLISIONREGISTRATION
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \tparam	C	Your type to register for collision
	/// \param [in,out]	c	Your "this" pointer for collision context
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename C>
	errcode SubmitCollisionRegistration(C*c);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	template <typename C> errcode Collidable::SubmitCollisionDeregistration(C*c);
	///
	/// \brief	Submit collision deregistration for your type.
	///\ingroup COLLISIONREGISTRATION
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \tparam	C	Your type.
	/// \param [in,out]	c	Your context pointer
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename C> 
	errcode SubmitCollisionDeregistration(C*c);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	const CollisionVolumeBSphere& Collidable::GetBSphere();
	///
	/// \brief	Gets b sphere.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	The b sphere.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	const CollisionVolume& GetCollisionVolume() const;

	
	errcode SetColliderModel(Model * mod, CollisionVolumeType vol);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Collidable::SetColliderModel(Model* mod);
	///
	/// \brief	Sets collider model.
	///\ingroup COLLISIONS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	mod	If non-null, the modifier.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Collidable::UpdateCollisionData(Matrix& mat);
	///
	/// \brief	Updates the collision data described by matrix.
	///\ingroup COLLISIONS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	mat	The matrix.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode UpdateCollisionData(Matrix& mat);

	std::list<Collidable*>::iterator GetDeletionIter();
	errcode SetDeletionIter(std::list<Collidable*>::iterator in );

	bool getColliding() const 
	{
		return colliding;
	};

	void setColliding(bool coll)
	{
		colliding = coll;
	};

	const CollisionVolumeBSphere& getBSphere() const
	{
		return *this->defaultBS;
	}

};

template <typename C>
errcode Collidable::SubmitCollisionRegistration(C*c)
{
	assert(regState == RegistrationState::DEREG);
	if (!regCommand)
	{
		regCommand = new CollisionRegistrationCommand<C>(c);
	}

	SceneManager::GetCurrentScene().SubmitCommand(regCommand);

	regState = RegistrationState::REG_PENDING;
	return errcode::success;
}

template <typename C>
errcode Collidable::SubmitCollisionDeregistration(C*c)
{
	assert(regState == RegistrationState::REG);
	if (!deregCommand)
	{
		deregCommand = new CollisionDeregistrationCommand<C>(c);
	}
	SceneManager::GetCurrentScene().SubmitCommand(deregCommand);

	regState = RegistrationState::DEREG_PENDING;
	return errcode::success;
}



#endif