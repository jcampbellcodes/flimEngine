#pragma once
#pragma once
#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "err.h"
#include "AzulCore.h"
#include "RegState.h"
#include <list>

#include "DrawableRegCommand.h"
#include "DrawableDeregCommand.h"

class Drawable
{
private:
	errcode SceneRegistration();
	errcode SceneDeregistration();

	friend class DrawableRegistrationCommand;
	friend class DrawableDeregistrationCommand;

	RegistrationState regState;

	DrawableRegistrationCommand* regCommand;
	DrawableDeregistrationCommand* deregCommand;

	std::list<Drawable*>::iterator deleteIter;

public:
	Drawable();
	virtual ~Drawable();
	Drawable(const Drawable&) = delete;
	const Drawable& operator= (const Drawable&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Drawable::Draw()
	/// \ingroup DEFINEGOS
	/// \brief	Draw callback to override.
	/// \ingroup BASICSCALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \par This will be called once a frame and should only contain code related to rendering.
	///
	/// \code
	/// 	 
	/// 	 errcode Frigate::Draw()
	///	{
	///
	///		// Place rendering code here.
	///
	///		// Render ship's graphics object to the current main camera via the Scene
	///		pGObj_SpaceFrigateLight->Render(&SceneManager::GetCurrentScene().GetCamera()->MainCamera());
	///
	///		return errcode::success;
	///	}
	/// 	 
	/// \endcode
	/// 
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode Draw() { return errcode::success; };

	virtual errcode Draw2D() { return errcode::success; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Drawable::SubmitDrawRegistration();
	///
	/// \brief	Submit draw registration.
	///\ingroup BASICSREGISTRATION
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \par Call this when you want to register an object for the rendering loop when it becomes active.
	/// 	 
	/// \code
	/// 	 
	/// 	 errcode Frigate::SceneEntry()
	///	{
	///
	///		// Registration
	///		SubmitDrawRegistration();
	///
	///		return errcode::success;
	///	} 
	/// \endcode
	/// 	
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitDrawRegistration();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Drawable::SubmitDrawDeregistration();
	///
	/// \brief	Submit draw deregistration.
	///\ingroup BASICSREGISTRATION
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \par Call this when you want to deregister an object that will be deactivated.
	/// \code
	/// 	
	///	errcode Frigate::SceneExit()
	///	{
	///		// Deregistration
	///		SubmitDrawDeregistration();
	///
	///		return errcode::success;
	///	}
	/// 	 
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitDrawDeregistration();

	std::list<Drawable*>::iterator GetDeletionIterator();
	errcode SetDeletionIterator(std::list<Drawable*>::iterator in);

	
};

#endif