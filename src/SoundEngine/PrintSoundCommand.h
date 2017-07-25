#pragma once
#ifndef PRINTSOUND_CALLBACK
#define PRINTSOUND_CALLBACK

#include "CallbackCommand.h"

class SoundCall;

class PrintSoundCommand : public CallbackCommand
{
public:
	PrintSoundCommand() = default;
	PrintSoundCommand(const PrintSoundCommand&) = default;
	PrintSoundCommand& operator=(const PrintSoundCommand&) = default;
	~PrintSoundCommand() = default;

	PrintSoundCommand(SoundCall* snd, const char* name);

	void execute() override;

	PrintSoundCommand* clone() { return nullptr; };

private:
	SoundCall* sound;
	const char* waveName;


};

#endif