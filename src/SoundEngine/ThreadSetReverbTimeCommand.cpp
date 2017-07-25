#include "ThreadSetReverbTimeCommand.h"

#include "Playlist.h"
#include "PlaylistManager.h"
#include "SoundManager.h"

void ThreadSetReverbTimeCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->SetReverbTime(cmd.reverbTime);
	}
}
