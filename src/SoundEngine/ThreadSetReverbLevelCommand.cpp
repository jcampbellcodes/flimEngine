#include "ThreadSetReverbLevelCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
void ThreadSetReverbLevelCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->SetReverbLevel(cmd.reverbLevel);
	}
}
