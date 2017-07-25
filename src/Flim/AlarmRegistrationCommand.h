#pragma once
#ifndef ALARMREGISTRATIONCOMMAND_H
#define ALARMREGISTRATIONCOMMAND_H

#include "Command.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmRegistrationCommand : public Command
{
public:
	AlarmRegistrationCommand() = delete;
	~AlarmRegistrationCommand() {
		//DebugMsg::out("Alarm Registration Command Cleaned\n");
	};
	AlarmRegistrationCommand(const AlarmRegistrationCommand&);
	AlarmRegistrationCommand& operator=(const AlarmRegistrationCommand&);

	AlarmRegistrationCommand(float time, Alarmable* in, AlarmableManager::ALARM_ID _id);

	virtual void execute() override;

private:
	Alarmable* alarm;
	AlarmableManager::ALARM_ID id;
	float t;
};

#endif 