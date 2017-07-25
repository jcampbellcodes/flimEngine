#include "ThreadSetReverbPredelayCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
void ThreadSetReverbPredelayCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->SetReverbPreDelay(cmd.reverbPredelay);
	}
}
