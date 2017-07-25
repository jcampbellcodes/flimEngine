#include "PlaylistStopCommand.h"
#include "Playlist.h"

PlaylistStopCommand::PlaylistStopCommand(Playlist * snd) : playlist(snd)
{
}

void PlaylistStopCommand::execute()
{
	if (playlist->IsPlaying())
	{
		playlist->Stop();
	}
}

PlaylistStopCommand * PlaylistStopCommand::clone()
{
	return nullptr;
}
