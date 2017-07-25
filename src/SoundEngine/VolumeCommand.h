#pragma once
#ifndef VolumeCOMMAND_H

#define VolumeCOMMAND_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class VolumeCommand : public AudioCommand
{
private:
	float VolumeFrom;
	const float VolumeTo;
	const float time;


public:
	VolumeCommand() = delete;
	VolumeCommand(Sound* snd, float from, float to, float time);
	VolumeCommand(float from, float to, float time);
	~VolumeCommand() {
		DebugMsg::out("Volume Command Cleaned\n");
	};
	VolumeCommand& operator=(const VolumeCommand&) = default;
	VolumeCommand(const VolumeCommand&) = default;

	VolumeCommand* clone() override;

	void execute() override;

};

#endif