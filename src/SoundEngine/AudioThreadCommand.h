#pragma once
#ifndef AUDIOTHREADCOMMAND
#define AUDIOTHREADCOMMAND

#include "Command.h"
#include "ThreadCommands.h"

class AudioThreadCommand : public Command
{
public:
	virtual void SetCommand(ThreadCommand& command) = 0;
};


#endif