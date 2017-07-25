#include "ThreadActivateFilterCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
void ThreadActivateFilterCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->ActivateFilter(cmd.filterType);
	}
}
