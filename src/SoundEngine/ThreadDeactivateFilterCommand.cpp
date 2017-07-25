#include "ThreadDeactivateFilterCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
void ThreadDeactivateFilterCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->DeactivateFilter(cmd.filterType);
	}
}
