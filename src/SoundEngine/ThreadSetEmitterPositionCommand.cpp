#include "ThreadSetEmitterPositionCommand.h"
#include "PlaylistManager.h"
#include "Playlist.h"
void ThreadSetEmitterPositionCommand::execute()
{
	Playlist* playlist = nullptr;
	if (PlaylistManager::GetPlaylist(playlist, cmd.handle) == snd_err::OK)
	{
		playlist->setEmitterPos(cmd.emitterPosX, cmd.emitterPosY, cmd.emitterPosZ);
	}
}
