#pragma once
#ifndef PLAYLISTFACTORY_H
#define PLAYLISTFACTORY_H

#include <list>
#include <stack>
#include "SoundCallRegistry.h"
#include "snd_err.h"

#define DEFAULT_INIT_PLAYLISTS 20

class Playlist;
class PlaylistInitializationCommand;

class PlaylistFactory // not a singleton... 
{
public:
	// construction -- takes in a list of initialization commands
	PlaylistFactory() = delete;
	PlaylistFactory(std::list<PlaylistInitializationCommand*> cmds, SoundCallID _id);
	~PlaylistFactory();

	snd_err CreatePlaylist(Playlist *& out, unsigned int instance, bool _3D);

	// only one of each!!!
	PlaylistFactory& operator=(const PlaylistFactory&) = delete;
	PlaylistFactory(const PlaylistFactory&) = delete;

	// methods

	// create playlist -- iterates through list of initialization commands and fires them off. Commands have been previously initialized with outside data such as
	//                    sound objects, audio commands, callback commands, etc. Just call cmd->AssociatePlaylist(playlist) and then cmd->Execute()
	snd_err CreatePlaylist(Playlist*& out, unsigned int instance);

	// return playlist -- puts playlist in the inactive pool and calls Clear() to remove all associated commands
	snd_err ReturnPlaylist(Playlist* toReturn);



private:
	// list of playlist initialization commands
	std::list<PlaylistInitializationCommand*> initCommands;

	// SoundCallID associated
	SoundCallID id;

	// active playlists
	std::list<Playlist*> activePool;

	// inactive playlists
	std::stack<Playlist*> inactivePool;
};

#endif