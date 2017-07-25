#include "ThreadPanCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "SoundManager.h"
#include "PlaylistPanCommand.h"
void ThreadPanCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		SoundManager::InsertTimelineCommand(new PlaylistPanCommand(playlist, cmd.from, cmd.to, cmd.time), cmd.triggerTime);
	}
}
