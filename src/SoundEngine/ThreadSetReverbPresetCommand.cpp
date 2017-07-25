#include "ThreadSetReverbPresetCommand.h"
#include "PlaylistManager.h"
#include "Playlist.h"
void ThreadSetReverbPresetCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->SetReverbPreset(cmd.reverbPreset);
	}
}
