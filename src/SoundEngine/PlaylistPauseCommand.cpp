#include "PlaylistPauseCommand.h"
#include "Playlist.h"

PlaylistPauseCommand::PlaylistPauseCommand(Playlist * play) : playlist(play)
{
}

void PlaylistPauseCommand::execute()
{
	playlist->Pause();
}

PlaylistPauseCommand * PlaylistPauseCommand::clone()
{
	return nullptr;
}
