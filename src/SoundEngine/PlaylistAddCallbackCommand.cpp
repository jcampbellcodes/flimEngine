#include "PlaylistAddCallbackCommand.h"
#include "Playlist.h"
#include "CallbackCommand.h"

PlaylistAddCallbackCommand::PlaylistAddCallbackCommand(CallbackCommand * command, int t, unsigned int id1, unsigned int id2) : cmd(command), time(t), playlist(nullptr), id(id1), secondaryID(id2)
{
	playlist = nullptr;
}

PlaylistAddCallbackCommand::PlaylistAddCallbackCommand(CallbackCommand * command, int t, unsigned int id1) : cmd(command), time(t), playlist(nullptr), id(id1), secondaryID(0)
{
	playlist = nullptr;
}

snd_err PlaylistAddCallbackCommand::AttachPlaylist(Playlist * p)
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

void PlaylistAddCallbackCommand::execute()
{
	assert(playlist);
	if (!secondaryID)
	{
		playlist->AddCommand(cmd->clone(), time, id);
	}
	else
	{
		playlist->AddCommand(cmd->clone(), time, id, secondaryID);
	}
}
