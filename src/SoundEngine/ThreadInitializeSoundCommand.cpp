#include "ThreadInitializeSoundCommand.h"
#include "PlaylistManager.h"
void ThreadInitializeSoundCommand::execute()
{
	PlaylistManager::InitializePlaylistDescriptor_SingleSound(cmd.scriptPath, cmd.id, cmd.loadedCallback);
}
