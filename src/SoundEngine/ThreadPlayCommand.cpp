#include "ThreadPlayCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "SoundManager.h"
#include "PlaylistPlayCommand.h"
void ThreadPlayCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		SoundManager::InsertTimelineCommand(new PlaylistPlayCommand(playlist, cmd.loop), cmd.triggerTime);
	}
}
