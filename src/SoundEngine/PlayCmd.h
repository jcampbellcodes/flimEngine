#pragma once
#ifndef PlayCOMMAND_H

#define PlayCOMMAND_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class PlayCommand : public AudioCommand
{
private:

public:
	PlayCommand();
	PlayCommand(Sound* snd);
	~PlayCommand() {
		//DebugMsg::out("Play Command Cleaned\n");
	};
	PlayCommand& operator=(const PlayCommand&) = default;
	PlayCommand(const PlayCommand&) = default;

	void execute() override;

	PlayCommand* clone() override;

};

#endif