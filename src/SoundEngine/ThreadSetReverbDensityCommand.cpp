#include "ThreadSetReverbDensityCommand.h"
#include "Playlist.h"

#include "PlaylistManager.h"
void ThreadSetReverbDensityCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->SetReverbDensity(cmd.reverbDensity);
	}
}
