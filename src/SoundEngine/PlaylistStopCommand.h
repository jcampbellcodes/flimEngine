#pragma once
#ifndef PlaylistStopCommand_H

#define PlaylistStopCommand_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class Playlist;

class PlaylistStopCommand : public AudioCommand
{
private:

	Playlist* playlist;

public:
	PlaylistStopCommand();
	PlaylistStopCommand(Playlist* snd);
	~PlaylistStopCommand() {
		//DebugMsg::out("Play Command Cleaned\n");
	};
	PlaylistStopCommand& operator=(const PlaylistStopCommand&) = default;
	PlaylistStopCommand(const PlaylistStopCommand&) = default;

	void execute() override;

	PlaylistStopCommand* clone() override;

};

#endif