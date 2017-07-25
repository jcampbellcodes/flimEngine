#include "ThreadStopCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "SoundManager.h"
#include "PlaylistStopCommand.h"

void ThreadStopCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		SoundManager::InsertTimelineCommand(new PlaylistStopCommand(playlist), cmd.triggerTime);
	}
}
