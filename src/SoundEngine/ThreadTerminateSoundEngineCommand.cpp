#include "ThreadTerminateSoundEngineCommand.h"
#include "SoundManager.h"
void ThreadTerminateSoundEngineCommand::execute()
{
	SoundManager::EndAudioThread();
}
