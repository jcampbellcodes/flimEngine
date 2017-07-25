#include "AudioCommand.h"

AudioCommand::AudioCommand()
{
	NUM_REPETITIONS = REPEAT_INDEFINITELY;
	trigger_time = 0;
	lerpFinished = true;
	sound = nullptr;
	playlist_id = 0x0;
}

AudioCommand::AudioCommand(Sound * snd)
{
	NUM_REPETITIONS = REPEAT_INDEFINITELY;
	trigger_time = 0;
	lerpFinished = true;
	sound = snd;
}

snd_err AudioCommand::AssignPlaylistID(unsigned int id)
{
	snd_err err = snd_err::OK;
	this->playlist_id = id;
	return err;
}

unsigned int AudioCommand::GetID()
{
	return playlist_id;
}

snd_err AudioCommand::AttachSound(Sound * snd)
{
	snd_err err = snd_err::OK;

	if (snd)
	{
		sound = snd;
	}
	else
	{
		err = snd_err::NULLPTR;
	}

	return err;
}
