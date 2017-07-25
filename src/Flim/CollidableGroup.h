#pragma once
#ifndef COLLIDABLEGROUP_H
#define COLLIDABLEGROUP_H

#include <set>
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollidableGroupDeleteCommand.h"
#include "err.h"

#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"

template <typename C>
class CollidableGroup : public Align16
{
public:


	// get const ref to collidable collection

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const std::set<C*>& CollidableGroup::GetCollection()
	///
	/// \brief	Gets the collection of collidables.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	Null if it fails, else the collection.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const std::set<C*>& GetCollection()
	{
		return Instance().privGetCollection();
	}

	// register

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode CollidableGroup::Register(C* c)
	///
	/// \brief	Registers a collidable to this group.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	c	Collidable to register
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Register(C* c)
	{
		return Instance().privRegister(c);
	}

	// deregister

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode CollidableGroup::Deregister(C* c)
	///
	/// \brief	Deregisters the collidable to this group.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	c	If non-null, the collidable to deregister.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Deregister(C* c)
	{
		return Instance().privDeregister(c);
	}

	//terminate

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode CollidableGroup::Terminate()
	///
	/// \brief	Singleton termination method.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Terminate()
	{
		return Instance().privTerminate();
	}

	static errcode setAABB(const Vect& min, const Vect& max)
	{
		return Instance().privSetAABB(min,max);
	}

	static const CollisionVolumeAABB& getAABB()
	{
		return Instance().privGetAABB();
	}

private:
	// big four

	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup& operator=(const CollidableGroup&) = delete;
	~CollidableGroup()
	{
		//DebugMsg::out("collidable group cleaned\n");
	}

	// singleton
	static CollidableGroup* instance;
	static CollidableGroup& Instance()
	{
		if (!instance)
		{
			instance = new CollidableGroup();
		}
		return *instance;
	}

	// collidable collection

	std::set<C*> collidables;

	// methods
	const std::set<C*>& privGetCollection();
	errcode privRegister(C* c);
	errcode privDeregister(C* c);
	errcode privTerminate();

	// Also has an AABB that is updated
	CollisionVolumeAABB collVolumeAABB;
	errcode privSetAABB(const Vect& min, const Vect& max);
	const CollisionVolumeAABB& privGetAABB();

};

template <typename C>
CollidableGroup<C>* CollidableGroup<C>::instance = nullptr;

template<typename C>
inline const std::set<C*>& CollidableGroup<C>::privGetCollection()
{
	return collidables;
}

template<typename C>
CollidableGroup<C>::CollidableGroup() : collVolumeAABB()
{
	// give the delete command to the collision manager -- or make it in the set 
	//SceneManager::GetCurrentScene().
	SceneManager::GetCurrentScene().collisionManager->AddDeleteCommand(new CollidableGroupDeleteCommand<C>());
}

template<typename C>
inline errcode CollidableGroup<C>::privRegister(C * c)
{
	errcode err = errcode::success;
	// add to the set
	collidables.insert(c);
	return err;
}

template<typename C>
inline errcode CollidableGroup<C>::privDeregister(C * c)
{
	errcode err = errcode::success;
	collidables.erase(c);
	return err;
}

template<typename C>
inline errcode CollidableGroup<C>::privTerminate()
{
	//DebugMsg::out("Collidable group cleaned!\n");
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}

	//clean up collidables here


	return errcode::success;
}

template<typename C>
inline errcode CollidableGroup<C>::privSetAABB(const Vect & min, const Vect & max)
{
	this->collVolumeAABB.SetMinMax(min, max);
	//Visualizer::ShowAABB(collVolumeAABB);
	return errcode::success;
}

template<typename C>
inline const CollisionVolumeAABB & CollidableGroup<C>::privGetAABB()
{
	return this->collVolumeAABB;
}


#endif // !COLLIDABLEGROUP

