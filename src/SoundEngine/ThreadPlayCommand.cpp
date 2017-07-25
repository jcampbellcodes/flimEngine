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
		//playlist->Play();
		SoundManager::InsertTimelineCommand(new PlaylistPlayCommand(playlist, cmd.loop), cmd.triggerTime);
	}
}
