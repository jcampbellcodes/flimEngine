#include "PlaylistPlayCommand.h"
#include "Playlist.h"
#include "PlaylistLoopCommand.h"

PlaylistPlayCommand::PlaylistPlayCommand()
{
}

PlaylistPlayCommand::PlaylistPlayCommand(Playlist * snd, bool toLoop) : playlist(snd), loop(toLoop)
{
}

void PlaylistPlayCommand::execute()
{
	playlist->Play(loop);
}

PlaylistPlayCommand * PlaylistPlayCommand::clone()
{
	return nullptr;
}
