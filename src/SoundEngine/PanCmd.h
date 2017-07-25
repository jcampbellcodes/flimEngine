#pragma once
#ifndef PanCOMMAND_H

#define PanCOMMAND_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class PanCommand : public AudioCommand
{
private:
	float panFrom;
	const float panTo;
	const float time;
	float delta;

public:
	PanCommand() = delete;
	PanCommand(Sound* snd, float from, float to, float time);
	PanCommand(float from, float to, float time);
	~PanCommand() {
		//DebugMsg::out("Pan Command Cleaned\n");
	};
	PanCommand& operator=(const PanCommand&) = default;
	PanCommand(const PanCommand&) = default;

	void execute() override;

	PanCommand* clone() override;

};

#endif