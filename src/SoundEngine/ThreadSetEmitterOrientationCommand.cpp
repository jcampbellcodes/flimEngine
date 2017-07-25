#include "ThreadSetEmitterOrientationCommand.h"
#include "Playlist.h"
#include "PlaylistManager.h"
void ThreadSetEmitterOrientationCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->setEmitterOrientation(cmd.emitterFrontX, cmd.emitterFrontY, cmd.emitterFrontZ, cmd.emitterTopX, cmd.emitterTopY, cmd.emitterTopZ);
	}
}
