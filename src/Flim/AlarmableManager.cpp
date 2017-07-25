#include "AlarmableManager.h"
#include "Alarmable.h"
#include "TimeManager.h"
#include "Flim.h"

AlarmableManager::AlarmableManager()
{
}

// t is time in milliseconds
errcode AlarmableManager::Register(float t, Alarmable * in, AlarmableManager::ALARM_ID id)
{
	// add alarmable to the map with t as a time

	// add the time to offset
	float offsetTime = FlimTime::TotalTime() + (t / 1000.0f);

	in->SetDeletionIter(static_cast<int>(id), this->timeline.insert(std::pair<float, AlarmableManager::AlarmEvent>(offsetTime, AlarmEvent(in, id))));

	return errcode::success;
}

errcode AlarmableManager::Deregister(Alarmable * in, AlarmableManager::ALARM_ID id)
{
	errcode err = errcode::success;
	// use iterator to remove
	if (!in)
	{
		err = errcode::badptr;
		return err;
	}
	
	if (in)
	{
		this->timeline.erase(in->GetDeletionIter(static_cast<int>(id)));
	}
	else
	{
		return errcode::badptr;
	}
	return errcode::success;
}

errcode AlarmableManager::ProcessAlarms()
{
	// get system time
	// see if first entry in map's key is <= Flim::TimeInSeconds

	// for now, deregister here
	// cannot dereference last iter
	// while iter >= system time, call trigger alarm

	std::multimap<float, AlarmEvent>::iterator iter = timeline.begin();

	float time = FlimTime::TotalTime();

	Alarmable* alarm = nullptr;
	AlarmableManager::ALARM_ID id;

	while (iter != timeline.end() && (iter->first <= time))
	{
		alarm = iter->second.first;
		id = iter->second.second;
		
		iter->second.first->SetRegistrationState(iter->second.second, RegistrationState::DEREG_PENDING);
		iter->second.first->AlarmDeregistration(iter->second.second);

		alarm->TriggerAlarm(id);

		iter = timeline.begin();
	}

	return errcode::success;
}
