#include "LoopCommand.h"
#include "Sound.h"

LoopCommand::LoopCommand(Sound * snd, bool p) : AudioCommand(snd), Loop(p)
{
}

LoopCommand::LoopCommand(bool p) : Loop(p)
{
}

void LoopCommand::execute()
{
	if (sound)
	{
		sound->Loop(Loop);
	}
}

LoopCommand * LoopCommand::clone()
{
	return new LoopCommand(*this);
}
