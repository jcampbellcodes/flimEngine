#include "MarkForStopCommand.h"
#include "SoundCall.h"
#include "PriorityManager.h"
#include "Trace\Trace.h"


MarkForStopCommand::MarkForStopCommand(SoundCall * snd) : attemptToStop(snd)
{
}

void MarkForStopCommand::execute()
{
	int priority = 0;
	attemptToStop->GetPriorityIndex(priority);
	snd_err err = PriorityManager::RemoveSound(priority);
	if (err != snd_err::OK)
	{
		Trace::out("\ncould not Stop: error!\n");
	}
	else
	{
		attemptToStop->SuccessfullyStop();
	}
}
