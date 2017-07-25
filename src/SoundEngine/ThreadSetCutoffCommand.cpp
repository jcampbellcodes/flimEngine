#include "ThreadSetCutoffCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
void ThreadSetCutoffCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->SetCutoff(cmd.filterCutoff);
	}
}
