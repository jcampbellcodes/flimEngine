#include "PlaylistAddCommand.h"
#include "AudioCommand.h"
#include "Playlist.h"

PlaylistAddCommand::PlaylistAddCommand(AudioCommand* command, int t, unsigned int _id) : cmd(command), time(t), playlist(nullptr), id(_id)
{
}

snd_err PlaylistAddCommand::AttachPlaylist(Playlist * p)
{
	snd_err err = snd_err::OK;
	if (p)
	{
		playlist = p;
	}
	else
	{
		err = snd_err::NULLPTR;
	}
	return err;
}

void PlaylistAddCommand::execute()
{
	assert(playlist);
	
	playlist->AddCommand(cmd->clone(), time, id);
}
