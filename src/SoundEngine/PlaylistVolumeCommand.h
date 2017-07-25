#pragma once
#ifndef PlaylistVolumeCommand_H

#define PlaylistVolumeCommand_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class Playlist;

class PlaylistVolumeCommand : public AudioCommand
{
private:
	float from;
	const float to;
	const float time;
	float delta;
	Playlist* playlist;

public:
	PlaylistVolumeCommand() = delete;
	PlaylistVolumeCommand(Playlist* snd, float from, float to, float time);
	PlaylistVolumeCommand(float from, float to, float time);
	~PlaylistVolumeCommand() {
		//DebugMsg::out("Pan Command Cleaned\n");
	};
	PlaylistVolumeCommand& operator=(const PlaylistVolumeCommand&) = default;
	PlaylistVolumeCommand(const PlaylistVolumeCommand&) = default;

	void execute() override;

	PlaylistVolumeCommand* clone() override;

};

#endif