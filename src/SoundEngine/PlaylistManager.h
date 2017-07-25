#pragma once
#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include "SoundCallRegistry.h"
#include "snd_err.h"
#include <list>
class PlaylistFactory;
class Playlist;

// enums to playlist factories
struct PlaylistDescriptor
{
	PlaylistDescriptor() = default;
	~PlaylistDescriptor();
	PlaylistDescriptor(const PlaylistDescriptor&) = default;
	PlaylistDescriptor& operator=(const PlaylistDescriptor&) = default;


	SoundCallID playlistID;
	PlaylistFactory* factory = nullptr;
};

class PlaylistManager
{
public:

	static snd_err InitializePlaylistDescriptor(std::string path_to_script, SoundCallID id, void(*cb)(void) = nullptr)
	{
		return Instance().privInitializePlaylistDescriptor(path_to_script, id, cb);
	}

	static snd_err InitializePlaylistDescriptor_SingleSound(std::string path_to_sound, SoundCallID id, void(*cb)(void) = nullptr)
	{
		return Instance().privInitializePlaylistDescriptor_SingleSound(path_to_sound, id, cb);
	}

	static snd_err StartPlaylist(SoundCallID id, unsigned int handle, bool is3D)
	{
		return Instance().privStartPlaylist(id, handle, is3D);
	}

	static snd_err StopPlaylist(unsigned int handle)
	{
		return Instance().privStopPlaylist(handle);
	}

	static snd_err GetPlaylist(Playlist*& p, unsigned int handle)
	{
		return Instance().privGetPlaylist(p, handle);
	}

	static snd_err Terminate()
	{
		return Instance().privTerminate();
	}

private:
	// big four
	PlaylistManager();
	PlaylistManager(const PlaylistManager&) = delete;
	PlaylistManager& operator=(const PlaylistManager&) = delete;
	~PlaylistManager();
	// singleton 
	static PlaylistManager* instance;
	static PlaylistManager& Instance()
	{
		if (!instance)
		{
			instance = new PlaylistManager();
		}
		return *instance;
	}

	// members
	// a linked list of playlistID/factory pairs
	std::list<PlaylistDescriptor*> playlistDescriptors;

	// list of active playlists
	std::list<Playlist*> activePlaylists;

	// private methods
	snd_err privInitializePlaylistDescriptor(std::string path_to_script, SoundCallID id, void(*cb)(void));
	snd_err privInitializePlaylistDescriptor_SingleSound(std::string path_to_script, SoundCallID id, void(*cb)(void));
	snd_err privStartPlaylist(SoundCallID id, unsigned int handle, bool is3D);
	snd_err privStopPlaylist(unsigned int handle);

	snd_err privGetPlaylist(Playlist*& p, unsigned int handle);

	snd_err privTerminate();


};

#endif