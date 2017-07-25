#pragma once
#ifndef PlaylistPlayCommand_H

#define PlaylistPlayCommand_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class Playlist;

class PlaylistPlayCommand : public AudioCommand
{
private:

	Playlist* playlist;
	bool loop;

public:
	PlaylistPlayCommand();
	PlaylistPlayCommand(Playlist* snd, bool toLoop);
	~PlaylistPlayCommand() {
		//DebugMsg::out("Play Command Cleaned\n");
	};
	PlaylistPlayCommand& operator=(const PlaylistPlayCommand&) = default;
	PlaylistPlayCommand(const PlaylistPlayCommand&) = default;

	void execute() override;

	PlaylistPlayCommand* clone() override;

};

#endif