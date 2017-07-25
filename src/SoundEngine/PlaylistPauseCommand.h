#pragma once
#ifndef PlaylistPauseCommand_H

#define PlaylistPauseCommand_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class Playlist;

class PlaylistPauseCommand : public AudioCommand
{
private:

	Playlist* playlist;

public:
	PlaylistPauseCommand();
	PlaylistPauseCommand(Playlist* playlist);
	~PlaylistPauseCommand() {
		//DebugMsg::out("Play Command Cleaned\n");
	};
	PlaylistPauseCommand& operator=(const PlaylistPauseCommand&) = default;
	PlaylistPauseCommand(const PlaylistPauseCommand&) = default;

	void execute() override;

	PlaylistPauseCommand* clone() override;

};

#endif