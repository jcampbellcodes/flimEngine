#include "ThreadPauseCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"

void ThreadPauseCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->Pause();
	}
}
