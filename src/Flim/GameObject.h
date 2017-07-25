#pragma once
#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "AzulCore.h"
#include "RegState.h"
#include "GameobjDeregCommand.h"
#include "GameobjRegCommand.h"
#include "err.h"

#include "Alarmable.h"
#include "Updatable.h"
#include "Inputable.h"
#include "Drawable.h"
#include "Collidable.h"

class GameObject : public Align16, public Updatable, public Drawable, public Inputable, public Alarmable, public Collidable
{
public:
	GameObject();
	virtual ~GameObject();
	GameObject& operator=(const GameObject&) = default;
	GameObject(const GameObject&) = default;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode GameObject::SubmitEntry();
	///
	/// \brief	Submit entry to the scene.
	/// \ingroup BASICS
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par Call this method when you want to tell the game that a deactivated object should be activated. Then SceneEntry() callback will soon follow.
	/// 	 
	/// \code
	/// 	 
	/// 	 deadObject->SubmitEntry();
	/// 	 
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitEntry();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode GameObject::SubmitExit();
	///
	/// \brief	Submit exit to the scene.
	/// \ingroup BASICS
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par When you want to kill an object, call this. Similar to a C++ destructor but Flim will recycle the object. Useful for factories, and calls the SceneExit callback
	/// \code
	/// 	 
	/// 	 objectToDie->SubmitExit();
	/// 	 
	/// \endcode
	/// 	 
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitExit();

private:
	RegistrationState regStateGO;

	GameObjectDeregistrationCommand* deregCommand;
	GameObjectRegistrationCommand* regCommand;

	friend class GameObjectRegistrationCommand;
	friend class GameObjectDeregistrationCommand;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode GameObject::SceneEntry()
	///
	/// \brief	Scene entry callback.
	///\ingroup BASICSCALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par This callback fires when a GameObject becomes active.
	/// 	 
	/// \code
	/// 	 
	/// 	 errcode Frigate::SceneEntry()
	///	{
	///
	///		// Registration
	///		SubmitUpdateRegistration();
	///		SubmitDrawRegistration();
	///
	///
	///		// Setting graphics member variables
	///		Matrix world;
	///		ShipPos.set(0, 20, 0);
	///		world = Matrix(TRANS, ShipPos);
	///		pGObj_SpaceFrigateLight->SetWorld(world);
	///
	///		return errcode::success;
	///	}
	/// 	 
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode SceneEntry() { return errcode::success; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode GameObject::SceneExit()
	///
	/// \brief	Scene exit callback. 
	///\ingroup BASICSCALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par This callback is called when a GameObject is deactivated.
	///
	/// \code
	/// 	 
	/// 	 errcode Frigate::SceneExit()
	///	{
	///		// Deregistration
	///		SubmitUpdateDeregistration();
	///		SubmitDrawDeregistration();
	///
	///		return errcode::success;
	///	}
	/// 	 
	/// \endcode
	/// 
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode SceneExit() { return errcode::success; };

	//errcode GameObject::SceneRegistration();
	//errcode GameObject::SceneDeregistration();

};

#endif // !GAMEOBJ_H
