#pragma once
#ifndef PlaylistPitchCommand_H

#define PlaylistPitchCommand_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"

class Playlist;

class PlaylistPitchCommand : public AudioCommand
{
private:
	float from;
	const float to;
	const float time;
	float delta;
	Playlist* playlist;

public:
	PlaylistPitchCommand() = delete;
	PlaylistPitchCommand(Playlist* snd, float from, float to, float time);
	PlaylistPitchCommand(float from, float to, float time);
	~PlaylistPitchCommand() {
		//DebugMsg::out("Pan Command Cleaned\n");
	};
	PlaylistPitchCommand& operator=(const PlaylistPitchCommand&) = default;
	PlaylistPitchCommand(const PlaylistPitchCommand&) = default;

	void execute() override;

	PlaylistPitchCommand* clone() override;

};

#endif