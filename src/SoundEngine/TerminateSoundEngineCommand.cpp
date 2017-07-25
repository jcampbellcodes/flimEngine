#include "TerminateSoundEngineCommand.h"
#include "SoundManager.h"

void TerminateSoundEngineCommand::execute()
{
	SoundManager::EndAudioThread();
}
