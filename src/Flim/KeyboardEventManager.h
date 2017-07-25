#pragma once
#ifndef KEYBOARDEVENTMANAGER_H
#define KEYBOARDEVENTMANAGER_H

#include "KeyEvent.h"
#include <map>

class KeyboardEventManager
{
public:

	KeyboardEventManager() = default;
	~KeyboardEventManager();
	KeyboardEventManager& operator=(const KeyboardEventManager&) = default;
	KeyboardEventManager(const KeyboardEventManager&) = default;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void KeyboardEventManager::Register(Inputable* in, AZUL_KEY k, input_type in_type);
	///
	/// \brief	Registers an inputable to a certain input event on the given key.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup INTERNAL
	/// \param [in,out]	in	   	Inputable to register.
	/// \param 		   	k	   	The AZUL_KEY to register to.
	/// \param 		   	in_type	Type of the input to register to.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Register(Inputable* in, AZUL_KEY k, input_type in_type);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void KeyboardEventManager::Deregister(Inputable* in, AZUL_KEY k, input_type in_type);
	///
	/// \brief Deregisters an inputable to a certain input event on the given key.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup INTERNAL
	/// \param [in,out]	in	   	Inputable to deregister.
	/// \param 		   	k	   	The AZUL_KEY to deregister.
	/// \param 		   	in_type	Type of the input to deregister.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Deregister(Inputable* in, AZUL_KEY k, input_type in_type);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void KeyboardEventManager::ProcessKeys();
	///
	/// \brief	Process the registered inputables.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void ProcessKeys();

private:

	std::map<AZUL_KEY, KeyEvent*> keyManagers;


};

#endif // !KEYBOARDEVENTMANAGER_H
