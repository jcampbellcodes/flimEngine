#include "Alarmable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TimeManager.h"

Alarmable::Alarmable()
{
	int i = 0;
	while (i < AlarmableManager::ALARM_NUMBER)
	{
		RegData[i].regState = RegistrationState::DEREG;
		// make the commands
		//regCommand = new AlarmRegistrationCommand(this);

		RegData[i].regCommand = nullptr;
		RegData[i].deregCommand = new AlarmDeregistrationCommand(this, static_cast<AlarmableManager::ALARM_ID>(i));
		RegData[i].startTime = 0;
		i++;
	}
}

Alarmable::~Alarmable()
{
	int i = 0;
	while (i < AlarmableManager::ALARM_NUMBER)
	{
		if (RegData[i].regState == RegistrationState::REG) // currently registered; ask to be deregistered
		{
			SubmitAlarmDeregistration(static_cast<AlarmableManager::ALARM_ID>(i));
		}
		else if (RegData[i].regState == RegistrationState::DEREG_PENDING)
		{
			AlarmDeregistration(static_cast<AlarmableManager::ALARM_ID>(i));
		}
		//SceneManager::Deregister(this, static_cast<AlarmableManager::ALARM_ID>(i));
		RegData[i].regState = RegistrationState::DEREG;
		if (RegData[i].regCommand)
		{
			delete RegData[i].regCommand;
			RegData[i].regCommand = nullptr;
		}
		if (RegData[i].deregCommand)
		{
			delete RegData[i].deregCommand;
			RegData[i].deregCommand = nullptr;
		}
		i++;
	}
	//DebugMsg::out("Alarmable Cleaned\n");
}

errcode Alarmable::AlarmRegistration(float t, AlarmableManager::ALARM_ID id)
{
	//assert(RegData[id].regState == RegistrationState::REG_PENDING);
	if (RegData[id].regState == RegistrationState::REG_PENDING)
	{
		SceneManager::Register(t, this, id);
		RegData[id].regState = RegistrationState::REG;
		RegData[id].startTime = FlimTime::TotalTime();
		return errcode::success;
	}
	else
	{
		return errcode::failure;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	float Alarmable::TimeLeft(AlarmableManager::ALARM_ID id)
///
/// \brief	Time left on one of the alarms.
///
/// \author	Jack Campbell
/// \date	3/12/2017
///
/// \param	id	The identifier.
/// 			
/// \par You can use this method to query how much time remains on a registered alarm. Calling this on a deregistered alarm returns 0.
/// 	 
/// \code
/// 	 
/// 	 float timeLeftOnAlarm0 = TimeLeft(AlarmableManager::ALARM_0);
/// 	 
/// \endcode
///
/// \return	A float.
////////////////////////////////////////////////////////////////////////////////////////////////////

float Alarmable::TimeLeft(AlarmableManager::ALARM_ID id)
{
	float t = 0;
	if (RegData[id].startTime) // 0 if not registered
	{
		t = FlimTime::TotalTime() - RegData[id].startTime;
	}
	return t;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	errcode Alarmable::ChangeTime(float t, AlarmableManager::ALARM_ID id)
///
/// \brief	Change time.
///
/// \author	Jack Campbell
/// \date	3/12/2017
///
/// \param	t 	The float to process.
/// \param	id	The identifier.
/// 			
/// 			
/// \par Returns errcode::failure if id is not registered. Otherwise deregisters the alarm and registers with the new time.
/// 	 
/// \code
/// 	
/// 	 // I want to reset ALARM_0 and make it fire in 1000 milliseconds
/// 	 ChangeTime(1000.0f, AlarmableManager::ALARM_0);
/// 	   
/// \endcode
///
/// \return	An errcode.
////////////////////////////////////////////////////////////////////////////////////////////////////

errcode Alarmable::ChangeTime(float t, AlarmableManager::ALARM_ID id)
{
	errcode err = errcode::failure;
	if (RegData[id].regState == RegistrationState::REG)
	{
		SubmitAlarmDeregistration(id);
		SubmitAlarmRegistration(t, id);
		err = errcode::success; 
	}

	return err;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	errcode Alarmable::AddTime(float t, AlarmableManager::ALARM_ID id)
///
/// \brief	Adds a time to 'id'.
///
/// \author	Jack Campbell
/// \date	3/12/2017
///
/// \param	t 	The float to process.
/// \param	id	The identifier.
/// \par Returns errcode::failure if id is not registered. Otherwise deregisters the alarm and registers with the time left plus the added time
///
/// \code
///
///		// ALARM_0 was set to fire in 10,000 milliseconds
/// 	 // I want to reset ALARM_0 and make it fire in 11,000 milliseconds
/// 	 AddTime(1000.0f, AlarmableManager::ALARM_0);
///
/// \endcode
/// \return	An errcode.
////////////////////////////////////////////////////////////////////////////////////////////////////

errcode Alarmable::AddTime(float t, AlarmableManager::ALARM_ID id)
{
	errcode err = errcode::failure;
	if (RegData[id].regState == RegistrationState::REG)
	{
		float newTime = (FlimTime::TotalTime() - RegData[id].startTime) + t;
		SubmitAlarmDeregistration(id);
		SubmitAlarmRegistration(newTime, id);
		err = errcode::success;
	}

	return err;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	errcode Alarmable::SubtractTime(float t, AlarmableManager::ALARM_ID id)
///
/// \brief	Subtract time.
///
/// \author	Jack Campbell
/// \date	3/12/2017
///
/// \param	t 	The float to process.
/// \param	id	The identifier.
/// \par Returns errcode::failure if id is not registered. Otherwise deregisters the alarm and registers with the time left minues the subtracted time
///
/// \code
///
///		// ALARM_0 was set to fire in 10,000 milliseconds
/// 	 // I want to reset ALARM_0 and make it fire in 9,000 milliseconds
/// 	 SubtractTime(1000.0f, AlarmableManager::ALARM_0);
///
/// \endcode
/// \return	An errcode.
////////////////////////////////////////////////////////////////////////////////////////////////////

errcode Alarmable::SubtractTime(float t, AlarmableManager::ALARM_ID id)
{
	errcode err = errcode::failure;
	if (RegData[id].regState == RegistrationState::REG)
	{
		float newTime = (FlimTime::TotalTime() - RegData[id].startTime) - t;
		SubmitAlarmDeregistration(id);
		SubmitAlarmRegistration(newTime, id);
		err = errcode::success;
	}

	return err;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	bool Alarmable::IsRegistered(AlarmableManager::ALARM_ID id)
///
/// \brief	Query if 'id' is registered.
///
/// \author	Jack Campbell
/// \date	3/12/2017
///
/// \param	id	The alarm check.
/// \par Returns whether the alarm at the ID is currently set to fire or not.
///
/// \return	True if registered, false if not.
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Alarmable::IsRegistered(AlarmableManager::ALARM_ID id)
{
	return (RegData[id].regState == RegistrationState::REG);
}

errcode Alarmable::SetDeletionIter(int alarmNumber, std::multimap<float, AlarmableManager::AlarmEvent>::const_iterator iter)
{
	RegData[alarmNumber].deleteIter = iter;
	return errcode::success;
}

std::multimap<float, AlarmableManager::AlarmEvent>::const_iterator Alarmable::GetDeletionIter(int alarmNumber)
{
	return RegData[alarmNumber].deleteIter;
}

errcode Alarmable::SetRegistrationState(int alarmNumber, RegistrationState state)
{
	RegData[alarmNumber].regState = state;
	return errcode::success;
}

void Alarmable::TriggerAlarm(AlarmableManager::ALARM_ID id)
{
	//RegData[id].regState = RegistrationState::DEREG;
	switch (id)
	{
	case AlarmableManager::ALARM_0:
		this->Alarm0();
		break;
	case AlarmableManager::ALARM_1:
		this->Alarm1();
		break;
	case AlarmableManager::ALARM_2:
		this->Alarm2();
		break;
	default:
		break;
	}
}

errcode Alarmable::AlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	//assert(RegData[id].regState == RegistrationState::DEREG_PENDING);
	if(RegData[id].regState == RegistrationState::DEREG_PENDING)
	{
		SceneManager::Deregister(this, id);
		RegData[id].regState = RegistrationState::DEREG;
		return errcode::success;
	}
	else
	{
		return errcode::failure;
	}
}

errcode Alarmable::SubmitAlarmRegistration(float t, AlarmableManager::ALARM_ID id)
{
	//assert(RegData[id].regState == RegistrationState::DEREG);
	if (RegData[id].regState == RegistrationState::DEREG)
	{
		// make this better
		RegData[id].regCommand = new AlarmRegistrationCommand(t, this, id);
	
		SceneManager::GetCurrentScene().SubmitCommand(RegData[id].regCommand);
		RegData[id].regState = RegistrationState::REG_PENDING;
		return errcode::success;
	}
	else
	{
		return errcode::failure;
	}
}


errcode Alarmable::SubmitAlarmDeregistration(AlarmableManager::ALARM_ID id)
{
	//assert(RegData[id].regState == RegistrationState::REG);
	if (RegData[id].regState == RegistrationState::REG)
	{
		SceneManager::GetCurrentScene().SubmitCommand(RegData[id].deregCommand);
		RegData[id].regState = RegistrationState::DEREG_PENDING;
		return errcode::success;
	}
	else
	{
		return errcode::failure;
	}
}
