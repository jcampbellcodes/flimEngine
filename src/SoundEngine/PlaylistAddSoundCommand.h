#pragma once
#ifndef PLAYLISTADDSOUND_H
#define PLAYLISTADDSOUND_H

#include "PlaylistInitCommand.h"
#include "snd_err.h"

class Playlist;
class Sound;

class PlaylistAddSoundCommand : public PlaylistInitializationCommand
{
public:
	PlaylistAddSoundCommand() = delete;
	PlaylistAddSoundCommand(unsigned int key);

	// load sound as you add it! may be replaced by bank system
	PlaylistAddSoundCommand(unsigned int key, const char* pathname, void(*cb)(void) = nullptr);
	PlaylistAddSoundCommand(const char*);
	virtual ~PlaylistAddSoundCommand() {
		//DebugMsg::out("PlaylistAddSound Command Cleaned\n");
	};
	PlaylistAddSoundCommand& operator=(const PlaylistAddSoundCommand&) = default;
	PlaylistAddSoundCommand(const PlaylistAddSoundCommand&) = default;


	virtual snd_err AttachPlaylist(Playlist*);
	virtual void execute();

private:
	unsigned int soundID;
	Playlist* playlist;


};

#endif