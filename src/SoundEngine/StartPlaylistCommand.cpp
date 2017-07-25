#include "StartPlaylistCommand.h"
#include "PlaylistManager.h"

StartPlaylistCommand::StartPlaylistCommand() : id(), handle(0)
{
}

StartPlaylistCommand::StartPlaylistCommand(SoundCallID _id, unsigned int _handle, bool _3D) : id(_id), handle(_handle), is3D(_3D)
{
}



snd_err StartPlaylistCommand::SetContext(SoundCallID _id, unsigned int _handle)
{
	snd_err err = snd_err::OK;

	id = _id;
	handle = _handle;

	return err;
}

void StartPlaylistCommand::execute()
{
	PlaylistManager::StartPlaylist(id, handle, is3D);
}
