#pragma once
#ifndef KEYEVENT_H
#define KEYEVENT_H
#include "AzulCore.h"
#include <list>
#include <map>
#include "InputType.h"

class Inputable;

class KeyEvent
{
public:
	KeyEvent() = default;
	~KeyEvent()
	{
 		//DebugMsg::out("KeyEventCleaned\n");
	}
	KeyEvent(const KeyEvent&) = default;
	KeyEvent& operator=(const KeyEvent&) = default;
	KeyEvent(AZUL_KEY k);

	void ProcessKeyEvent();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void KeyEvent::Deregister(Inputable* a, input_type evnt);
	///
	/// \brief	Deregisters this key in the context of the inputable.
	/// \ingroup INTERNAL
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	a   	If non-null, the Inputable to deregister.
	/// \param 		   	evnt	The event to deregister.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Deregister(Inputable* a, input_type evnt);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void KeyEvent::Register(Inputable* a, input_type evnt);
	///
	/// \brief	Registers this inputable to an input event on this key.
	///\ingroup INTERNAL
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	a   	If non-null, the Inputable to register.
	/// \param 		   	evnt	The event to register to.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Register(Inputable* a, input_type evnt);

private:

	AZUL_KEY Key;

	bool keyChange;

	std::map<AZUL_KEY, KeyEvent*>::const_iterator deleteIter;

	// every inputable being watched
	std::list<Inputable*> PressedObjects;
	std::list<Inputable*> ReleasedObjects;

};

#endif // !KEYEVENT_H
