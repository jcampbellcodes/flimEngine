#pragma once
#ifndef ALARMABLEMANAGER_H
#define ALARMABLEMANAGER_H

#include <map>
#include "AzulCore.h"
#include "err.h"
class Alarmable;

class AlarmableManager
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \enum	ALARM_ID
	///
	/// \brief	Values that represent alarm Identifiers.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	enum ALARM_ID {ALARM_0, ALARM_1, ALARM_2};


	/// \brief	The alarm number
	static const int ALARM_NUMBER = 3;


	// big four
	AlarmableManager();
	~AlarmableManager() 
	{
		//DebugMsg::out("AlarmableManager cleaned\n"); 
	};
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager& operator=(const AlarmableManager&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode AlarmableManager::Register(float t, Alarmable* in, AlarmableManager::ALARM_ID id);
	///
	/// \brief	Registers the alarm to go off after t milliseconds
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param 		   	t 	The amount of time to register the alarm to
	/// \param [in,out]	in	If non-null, the alarmable.
	/// \param 		   	id	The ID of the alarm to register
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Register(float t, Alarmable* in, AlarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode AlarmableManager::Deregister(Alarmable* in, AlarmableManager::ALARM_ID id);
	///
	/// \brief	Deregisters the alarmable per one ID.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	If non-null, the alarmable.
	/// \param 		   	id	The ID of the alarm to deregister
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Deregister(Alarmable* in, AlarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode AlarmableManager::ProcessAlarms();
	///
	/// \brief	Process the alarms.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode ProcessAlarms();

private:

	friend class Alarmable;

	using AlarmEvent = std::pair<Alarmable*, ALARM_ID>;
	std::multimap<float, AlarmEvent> timeline;

};

#endif