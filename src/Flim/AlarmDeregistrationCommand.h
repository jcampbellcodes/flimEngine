#pragma once
#ifndef ALARMDEREGISTRATIONCOMMAND_H
#define ALARMDEREGISTRATIONCOMMAND_H

#include "Command.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmDeregistrationCommand : public Command
{
public:
	AlarmDeregistrationCommand() = delete;
	~AlarmDeregistrationCommand() {
		//DebugMsg::out("Alarm Deregistration Command Cleaned\n");
	};
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand&) = default;
	AlarmDeregistrationCommand& operator=(const AlarmDeregistrationCommand&) = default;

	AlarmDeregistrationCommand(Alarmable* in, AlarmableManager::ALARM_ID _id);


	virtual void execute() override;

private:

	Alarmable* alarm;
	AlarmableManager::ALARM_ID id;

};

#endif 