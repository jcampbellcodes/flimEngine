#include "AlarmRegistrationCommand.h"
#include "Alarmable.h"
#include "SceneManager.h"
#include "AlarmableManager.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(float time, Alarmable * in, AlarmableManager::ALARM_ID _id) : alarm(in), t(time), id(_id)
{
}

void AlarmRegistrationCommand::execute()
{
	//SceneManager::Register(t, alarm, id);
	alarm->AlarmRegistration(t, id);
}
