#pragma once

#ifndef Drawable_MANAGER_H
#define Drawable_MANAGER_H

#include <list>
#include "AzulCore.h"

#include "Drawable.h"

class DrawableManager
{
private:

	using StorageList = std::list<Drawable*>;
	StorageList storageList;

	friend class Scene;
	errcode ProcessElements();

public:

	// big four
	DrawableManager() = default;
	~DrawableManager() { /*DebugMsg::out("DrawableManager cleaned\n");*/ };
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator=(const DrawableManager&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode DrawableManager::Register(Drawable* in);
	///
	/// \brief	Registers this drawable to the scene.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	If non-null, the drawable to register.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Register(Drawable* in);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode DrawableManager::Deregister(Drawable* in);
	///
	/// \brief	Deregisters this drawable.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	If non-null, the drawable to deregister.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Deregister(Drawable* in);

};

#endif // !Drawable_MANAGER_H