#pragma once
#ifndef LoopCOMMAND_H

#define LoopCOMMAND_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class LoopCommand : public AudioCommand
{
private:
	const bool Loop;

public:
	LoopCommand() = delete;
	LoopCommand(Sound* snd, bool p);
	LoopCommand(bool p);
	~LoopCommand() {
		//DebugMsg::out("Loop Command Cleaned\n");
	};
	LoopCommand& operator=(const LoopCommand&) = default;
	LoopCommand(const LoopCommand&) = default;

	void execute() override;

	LoopCommand* clone() override;

};

#endif