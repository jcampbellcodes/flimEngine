#pragma once
#ifndef AudioCommand_H

#define AudioCommand_H

#include "AzulCore.h"
#include "Command.h"
#include "snd_err.h"

#define REPEAT_INDEFINITELY -1

class Sound;

class AudioCommand : public Command
{
protected:
	friend class SoundManager;
	friend class Executioner;
	friend class Timeline;
	// parameters
	int NUM_REPETITIONS;
	int trigger_time;
	bool lerpFinished;

	unsigned int playlist_id;

	Sound* sound;

public:
	AudioCommand();
	AudioCommand(Sound* snd);
	virtual ~AudioCommand() {
		//DebugMsg::out("Base AudioCommand Cleaned\n");
	};
	AudioCommand& operator=(const AudioCommand&) = default;
	AudioCommand(const AudioCommand&) = default;

	snd_err AssignPlaylistID(unsigned int);
	unsigned int GetID();

	virtual void execute() {};

	virtual snd_err AttachSound(Sound* snd);

	virtual AudioCommand* clone() = 0;

	std::multimap<int, AudioCommand*>::iterator deleteIter;
};

#endif