#pragma once
#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "err.h"
#include "RegState.h"
#include "AzulCore.h"
#include <list>

class Updatable
{
private:
	errcode SceneRegistration();
	errcode SceneDeregistration();

	friend class UpdatableRegistrationCommand;
	friend class UpdatableDeregistrationCommand;

	RegistrationState regState;
	UpdatableDeregistrationCommand* deregCommand;
	UpdatableRegistrationCommand* regCommand;

public:
	Updatable();
	virtual ~Updatable();
	Updatable(const Updatable&) = delete;
	const Updatable& operator= (const Updatable&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Updatable::Update()
	///
	/// \brief	Called every frame
	/// \ingroup BASICSCALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par Update is called once a frame on objects that have been registered to update.
	/// 		
	/// \code
	/// 	 
	/// 	 errcode Frigate::Update()
	///	{
	///
	///		// Place frame related content here. This code moves the ship's graphics object.
	///
	///		// Ship translation movement (not using time-based values for simplicity)
	///		if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	///		{
	///			ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
	///		}
	///		else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	///		{
	///			ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
	///		}
	///
	///		// Spaceship adjust matrix
	///		Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	///		pGObj_SpaceFrigateLight->SetWorld(world);
	///
	///		return errcode::success;
	///	}
	/// 	 
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode Update() { return errcode::success; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Updatable::SubmitUpdateRegistration();
	///
	/// \brief	Submit update registration.
	/// \ingroup BASICSREGISTRATION
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par When a GameObject enters a scene, you may want to register it for updates.
	///
	/// \code
	/// 	 
	/// 	 errcode Frigate::SceneEntry()
	///	{
	///
	///		// Registration
	///		SubmitUpdateRegistration();
	///
	///		return errcode::success;
	///	}
	/// 	 
	/// \endcode
	/// 
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitUpdateRegistration();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Updatable::SubmitUpdateDeregistration();
	///
	/// \brief	Submit update deregistration.
	/// \ingroup BASICSREGISTRATION
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par Remember to deregister any object that was registered when it is time to delete or recycle the object.
	///
	/// \code
	/// 	 errcode Frigate::SceneExit()
	///	{
	///		// Deregistration
	///		SubmitUpdateDeregistration();
	///
	///		return errcode::success;
	///	}
	/// \endcode
	/// 
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitUpdateDeregistration();

	std::list<Updatable*>::iterator deleteIter;

};

#endif