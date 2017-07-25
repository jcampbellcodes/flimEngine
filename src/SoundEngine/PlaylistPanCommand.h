#pragma once
#ifndef PlaylistPanCommand_H

#define PlaylistPanCommand_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class Playlist;

class PlaylistPanCommand : public AudioCommand
{
private:
	float from;
	const float to;
	const float time;
	float delta;
	Playlist* playlist;

public:
	PlaylistPanCommand() = delete;
	PlaylistPanCommand(Playlist* play, float from, float to, float time);
	PlaylistPanCommand(float from, float to, float time);
	~PlaylistPanCommand() {
		//DebugMsg::out("Pan Command Cleaned\n");
	};
	PlaylistPanCommand& operator=(const PlaylistPanCommand&) = default;
	PlaylistPanCommand(const PlaylistPanCommand&) = default;

	void execute() override;

	PlaylistPanCommand* clone() override;

};

#endif