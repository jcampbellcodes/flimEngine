#include "ThreadSetReverbSizeCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "SoundManager.h"
void ThreadSetReverbSizeCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->SetReverbSize(cmd.reverbSize);
	}
}
