#pragma once
#ifndef PitchCOMMAND_H

#define PitchCOMMAND_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class PitchCommand : public AudioCommand
{
private:
	float PitchFrom;
	const float PitchTo;
	const float time;

	float delta;

public:
	PitchCommand() = delete;
	PitchCommand(Sound* snd, float from, float to, float time);
	PitchCommand(float from, float to, float time);
	~PitchCommand() {
		DebugMsg::out("Pitch Command Cleaned\n");
	};
	PitchCommand& operator=(const PitchCommand&) = default;
	PitchCommand(const PitchCommand&) = default;

	void execute() override;

	PitchCommand* clone() override;

};

#endif