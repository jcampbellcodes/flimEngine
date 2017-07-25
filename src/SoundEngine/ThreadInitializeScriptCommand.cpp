#include "ThreadInitializeScriptCommand.h"
#include "PlaylistManager.h"
void ThreadInitializeScriptCommand::execute()
{
	PlaylistManager::InitializePlaylistDescriptor(cmd.scriptPath, cmd.id, cmd.loadedCallback);

}
