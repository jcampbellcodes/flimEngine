#pragma once
#ifndef PlaylistAdd_H
#define PlaylistAdd_H

#include "PlaylistInitCommand.h"
#include "AudioCommand.h"
#include "snd_err.h"

class Playlist;
//class AudioCommand;

class PlaylistAddCommand : public PlaylistInitializationCommand
{
public:
	PlaylistAddCommand() = delete;
	PlaylistAddCommand(AudioCommand* cmd, int time, unsigned int id);
	virtual ~PlaylistAddCommand() {
		//DebugMsg::out("PlaylistAdd Command Cleaned\n");
	};
	PlaylistAddCommand& operator=(const PlaylistAddCommand&) = default;
	PlaylistAddCommand(const PlaylistAddCommand&) = default;


	virtual snd_err AttachPlaylist(Playlist*);
	virtual void execute();

private:
	AudioCommand* cmd;
	int time;
	unsigned int id;
	Playlist* playlist;


};

#endif