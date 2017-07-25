#include "ThreadVolumeCommand.h"
#include "PlaylistManager.h"
#include "SoundManager.h"
#include "PlaylistVolumeCommand.h"
void ThreadVolumeCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		SoundManager::InsertTimelineCommand(new PlaylistVolumeCommand(playlist, cmd.from, cmd.to, cmd.time), cmd.triggerTime);
	}
}
