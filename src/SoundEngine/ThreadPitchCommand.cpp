#include "ThreadPitchCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "SoundManager.h"
#include "PlaylistPitchCommand.h"
void ThreadPitchCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		//playlist->Pitch(cmd.pitch);
		SoundManager::InsertTimelineCommand(new PlaylistPitchCommand(playlist, cmd.from, cmd.to, cmd.time), cmd.triggerTime);
	}
}
