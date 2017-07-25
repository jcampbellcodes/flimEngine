#include "MarkForPlayCommand.h"
#include "SoundCall.h"
#include "PriorityManager.h"
#include "Trace\Trace.h"


MarkForPlayCommand::MarkForPlayCommand(SoundCall * snd, int & index) : attemptToPlay(snd), priorityIndex(index)
{
}

void MarkForPlayCommand::execute()
{
	snd_err err = PriorityManager::AttemptToPlay(attemptToPlay, priorityIndex);
	if (err != snd_err::OK)
	{
		Trace::out("\ncould not play: not enough room!\n");
	}
	else
	{
		attemptToPlay->SuccessfullyPlay(priorityIndex);
	}
}
