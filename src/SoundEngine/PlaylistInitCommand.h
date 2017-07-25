#pragma once
#ifndef PLAYLISTINIT_H
#define PLAYLISTINIT_H

#include "Command.h"
#include "snd_err.h"

class Playlist;

class PlaylistInitializationCommand : public Command
{
public:
	PlaylistInitializationCommand() = default;
	virtual ~PlaylistInitializationCommand() {
		//DebugMsg::out("PlaylistInitialization Command Cleaned\n");
	};
	PlaylistInitializationCommand& operator=(const PlaylistInitializationCommand&) = default;
	PlaylistInitializationCommand(const PlaylistInitializationCommand&) = default;


	virtual snd_err AttachPlaylist(Playlist*) = 0;
	virtual void execute() = 0;
private:


};

#endif