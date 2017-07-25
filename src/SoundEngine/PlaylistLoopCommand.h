#pragma once
#ifndef PlaylistLoopCommand_H

#define PlaylistLoopCommand_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class Playlist;

class PlaylistLoopCommand : public AudioCommand
{
private:

	Playlist* playlist;
	bool loop;

public:
	PlaylistLoopCommand();
	PlaylistLoopCommand(Playlist* snd, bool toLoop);
	~PlaylistLoopCommand() {
		//DebugMsg::out("Play Command Cleaned\n");
	};
	PlaylistLoopCommand& operator=(const PlaylistLoopCommand&) = default;
	PlaylistLoopCommand(const PlaylistLoopCommand&) = default;

	void execute() override;

	PlaylistLoopCommand* clone() override;

};

#endif