#include "PlayCmd.h"

PlayCommand::PlayCommand(Sound * snd) : AudioCommand(snd)
{ 
}

PlayCommand::PlayCommand()
{
}

void PlayCommand::execute()
{
	if (sound)
	{
		sound->Play();
	}
}

PlayCommand * PlayCommand::clone()
{
	return new PlayCommand(*this);
}
