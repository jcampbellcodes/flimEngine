#include "PlaylistLoopCommand.h"
#include "Playlist.h"
#include "PlaylistLoopCommand.h"

PlaylistLoopCommand::PlaylistLoopCommand()
{
}

PlaylistLoopCommand::PlaylistLoopCommand(Playlist * snd, bool toLoop) : playlist(snd), loop(toLoop)
{
}

void PlaylistLoopCommand::execute()
{
	playlist->Loop(loop);
}

PlaylistLoopCommand * PlaylistLoopCommand::clone()
{
	return nullptr;
}
