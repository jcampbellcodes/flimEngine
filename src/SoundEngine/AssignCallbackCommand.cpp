#include "AssignCallbackCommand.h"

AssignCallbackCommand::AssignCallbackCommand(CallbackCommand * _cmd, Sound * _snd) : AudioCommand(_snd), cmd(_cmd)
{
}

AssignCallbackCommand::AssignCallbackCommand(CallbackCommand * _cmd) : cmd(_cmd)
{
}

void AssignCallbackCommand::execute()
{
	if (sound)
	{
		sound->SubmitCallback(cmd);
	}
}

AssignCallbackCommand * AssignCallbackCommand::clone()
{
	return new AssignCallbackCommand(*this);
}
