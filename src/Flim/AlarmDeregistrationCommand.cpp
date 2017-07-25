#include "AlarmDeregistrationCommand.h"
#include "Alarmable.h"
#include "SceneManager.h"

AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable * in, AlarmableManager::ALARM_ID _id) : alarm(in), id(_id)
{

}

void AlarmDeregistrationCommand::execute()
{
	//SceneManager::Deregister(alarm, id);
	alarm->AlarmDeregistration(id);
}
