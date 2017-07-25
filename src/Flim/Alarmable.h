#pragma once
#ifndef ALARMABLE_H
#define ALARMABLE_H

#include "AzulCore.h"
#include "Flim.h"

#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"
#include "RegState.h"
#include "err.h"
#include "AlarmableManager.h"

#include <map>

class Alarmable
{
public:
	Alarmable();
	Alarmable& operator=(const Alarmable&);
	virtual ~Alarmable();
	Alarmable(const Alarmable&);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);
	///
	/// \brief	Submit alarm deregistration.
	/// \ingroup ALARMREGISTRATION
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \addtogroup REGALARMS
	/// \param	id	The identifier.
	/// 			
	/// 			
	/// 			\code
	///	errcode Frigate::SceneExit()
	///	{
	///
	///		//...
	///
	///		SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	///		SubmitAlarmDeregistration(AlarmableManager::ALARM_1);
	///		SubmitAlarmDeregistration(AlarmableManager::ALARM_2);
	///
	///		//...
	///		return errcode::success;
	///	}
	///	\endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Alarmable::SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id);
	///
	/// \brief	Submit alarm registration.
	/// \ingroup ALARMREGISTRATION
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \addtogroup REGALARMS
	/// \param	t 	The float to process.
	/// \param	id	The identifier.
	/// 			
	/// 			errcode Frigate::SceneEntry()
	///	{
	///		//...
	///
	///		SubmitAlarmRegistration(1000.0f, AlarmableManager::ALARM_0);
	///		SubmitAlarmRegistration(5000.0f, AlarmableManager::ALARM_1);
	///		SubmitAlarmRegistration(8000.0f, AlarmableManager::ALARM_2);
	///		//...
	///	}
	///
	///	\endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id);


	//user defined

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual void Alarmable::Alarm0()
	///
	/// \brief	Alarm 0 callback.
	///\ingroup ALARMCALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \par Callback for alarms
	/// 		
	/// 		\code
	///
	///	void Frigate::Alarm0()
	///	{
	///		DebugMsg::out("\n\nFIRST FRIGATE ALARMED\n\n");
	///	}
	///
	///	void Frigate::Alarm1()
	///	{
	///		DebugMsg::out("\n\nSECOND FRIGATE ALARMED\n\n");
	///	}
	///
	///	void Frigate::Alarm2()
	///	{
	///		DebugMsg::out("\n\nTHIRD FRIGATE ALARMED\n\n\n");
	///	}
	///
	///	\endcode
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Alarm0() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual void Alarmable::Alarm1()
	///
	/// \brief	Alarm 1 callback.
	///\ingroup ALARMCALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par see alarm0
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Alarm1() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual void Alarmable::Alarm2()
	///
	/// \brief	Alarm 2 callback.
	///\ingroup ALARMCALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		\par see alarm0
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Alarm2() {};

	float TimeLeft(AlarmableManager::ALARM_ID id);

	errcode ChangeTime(float t, AlarmableManager::ALARM_ID id);
	errcode AddTime(float t, AlarmableManager::ALARM_ID id);
	errcode SubtractTime(float t, AlarmableManager::ALARM_ID id);
	bool IsRegistered(AlarmableManager::ALARM_ID id);

	errcode SetDeletionIter(int alarmNumber, std::multimap<float, AlarmableManager::AlarmEvent>::const_iterator iter);
	std::multimap<float, AlarmableManager::AlarmEvent>::const_iterator GetDeletionIter(int alarmNumber);

	errcode SetRegistrationState(int alarmNumber, RegistrationState state);

private:

	struct RegistrationData
	{
		RegistrationState regState;
		std::multimap<float, AlarmableManager::AlarmEvent>::const_iterator deleteIter;
		AlarmRegistrationCommand* regCommand;
		AlarmDeregistrationCommand* deregCommand;
		float startTime;
	};

	friend class AlarmRegistrationCommand;
	friend class AlarmDeregistrationCommand;
	friend class AlarmableManager;

	RegistrationData RegData[AlarmableManager::ALARM_NUMBER];

	void TriggerAlarm(AlarmableManager::ALARM_ID id);

	errcode AlarmDeregistration(AlarmableManager::ALARM_ID id);
	errcode AlarmRegistration(float t, AlarmableManager::ALARM_ID id);

};

#endif // !ALARMABLE_H
