#include "ThreadLoopCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "SoundManager.h"
#include "PlaylistLoopCommand.h"
void ThreadLoopCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		SoundManager::InsertTimelineCommand(new PlaylistLoopCommand(playlist, cmd.loop), cmd.triggerTime);
	}
}
