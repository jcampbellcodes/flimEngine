#pragma once
#ifndef UPDATABLE_MANAGER_H
#define UPDATABLE_MANAGER_H

#include <list>
#include "AzulCore.h"

#include "Updatable.h"

class UpdatableManager
{
private:

	using StorageList = std::list<Updatable*>;
	StorageList storageList;

	friend class Scene;
	errcode ProcessElements();

public:

	// big four
	UpdatableManager() = default;
	~UpdatableManager() { /*DebugMsg::out("UpdatableManager cleaned\n");*/ };
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator=(const UpdatableManager&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode UpdatableManager::Register(Updatable* in);
	///
	/// \brief	Registers an updatable to the scene.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	Updatable to register.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Register(Updatable* in);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode UpdatableManager::Deregister(Updatable* in);
	///
	/// \brief	Deregisters an updatable to the scene.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	Updatable to deregister
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Deregister(Updatable* in);

};

#endif // !UPDATABLE_MANAGER_H
