#include "PlaylistAddSoundCommand.h"
#include "Sound.h"
#include "Playlist.h"
#include "HashThis.h"

#include "SoundManager.h"

// preferable -- hash early
PlaylistAddSoundCommand::PlaylistAddSoundCommand(unsigned int sndID) : soundID(sndID), playlist(nullptr)
{
}

// preferable -- hash early
PlaylistAddSoundCommand::PlaylistAddSoundCommand(unsigned int sndID, const char* pathname, void(*cb)(void)) : soundID(sndID), playlist(nullptr)
{
	SoundManager::LoadSound(sndID, pathname, cb);
}

PlaylistAddSoundCommand::PlaylistAddSoundCommand(const char* sndID)
{
	soundID = HashThis(sndID);
	playlist = nullptr;
}

snd_err PlaylistAddSoundCommand::AttachPlaylist(Playlist *p )
{
	snd_err err = snd_err::OK;

	if (p)
	{
		playlist = p;
	}
	else
	{
		err = snd_err::ERR;
	}
	return err;
}

void PlaylistAddSoundCommand::execute()
{
	assert(playlist);
	playlist->AddSound(soundID);
}
