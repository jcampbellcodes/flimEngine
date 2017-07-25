#include "ThreadCreatePlaylistCommand.h"
#include "PlaylistManager.h"
void ThreadCreatePlaylistCommand::execute()
{
	PlaylistManager::StartPlaylist(cmd.id, cmd.handle, cmd.is3D);
}
