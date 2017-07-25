#pragma once
#ifndef INPUTABLE_H
#define INPUTABLE_H

#include "KeyEvent.h"
#include "err.h"
#include "RegState.h"


class Inputable
{
private:
	errcode SceneRegistration(AZUL_KEY key, input_type type);
	errcode SceneDeregistration(AZUL_KEY key, input_type type);

	friend class InputableRegistrationCommand;
	friend class InputableDeregistrationCommand;

	RegistrationState regState;
	InputableDeregistrationCommand* deregCommand;
	InputableRegistrationCommand* regCommand;





	std::list<Inputable*>::iterator deleteIter;

public:
	Inputable();
	virtual ~Inputable();
	Inputable(const Inputable&) = delete;
	const Inputable& operator= (const Inputable&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Inputable::KeyPressed(AZUL_KEY key)
	///
	/// \brief	Key pressed callback.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \ingroup INPUTCALLBACKS
	/// \param	key	Hook to check the key.
	/// 			\par Place code in this callback if you are registered for a press
	/// 				  event.
	/// \code
	/// 	 
	/// 	 errcode Frigate::KeyPressed(AZUL_KEY key)
	///	{
	///		if (key == AZUL_KEY::KEY_SPACE)
	///		{
	///			DebugMsg::out("pressed\n");
	///		}
	///		return errcode::success;
	///	}
	///	\endcode
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode KeyPressed(AZUL_KEY key) { key; return errcode::success; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Inputable::KeyReleased(AZUL_KEY key)
	///
	/// \brief	Key released.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup INPUTCALLBACKS
	/// \param	key	Hook to check the key.
	/// 			
	/// \par Place code in this callback if you are registered for a release event.
	/// \code
	/// 	  
	/// 	  errcode Frigate::KeyReleased(AZUL_KEY key)
	///	{
	///		if (key == AZUL_KEY::KEY_SPACE)
	///		{
	///			DebugMsg::out("released\n");
	///		}
	///		return errcode::success;
	///	}
	/// 	   
	/// \endcode 
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode KeyReleased(AZUL_KEY key) { key; return errcode::success; };


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Inputable::SubmitInputRegistration(AZUL_KEY key, input_type type);
	///
	/// \brief	Submit input registration.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup INPUTREGISTRATION
	/// \param	key 	The key.
	/// \param	type	The input type.
	/// \par Register for input any objects that you would like to receive input on.
	/// 				
	/// \code
	/// 	 
	/// 	 errcode Frigate::SceneEntry()
	///	{
	///		//...
	///		SubmitInputRegistration(AZUL_KEY::KEY_SPACE, input_type::pressed);
	///		SubmitInputRegistration(AZUL_KEY::KEY_SPACE, input_type::released);
	///		//...
	///		return errcode::success;
	///	}
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitInputRegistration(AZUL_KEY key, input_type type);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Inputable::SubmitInputDeregistration(AZUL_KEY key, input_type type);
	///
	/// \brief	Submit input deregistration.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup INPUTREGISTRATION
	/// \param	key 	The key.
	/// \param	type	The input type.
	/// \par Remember to deregister input when an object is no longer active!
	/// 				
	/// 				
	/// \code
	/// 	 
	/// 	 errcode Frigate::SceneExit()
	///	{
	///		//...
	///
	///		SubmitInputDeregistration(AZUL_KEY::KEY_E, input_type::pressed);
	///		SubmitInputDeregistration(AZUL_KEY::KEY_E, input_type::released);
	///
	///		//...
	///		return errcode::success;
	///	}
	/// 	 
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitInputDeregistration(AZUL_KEY key, input_type type);

	std::list<Inputable*>::iterator GetDeletionIterator();

	errcode SetDeletionIterator(std::list<Inputable*>::iterator in);

};

#endif // !INPUTABLE_H
