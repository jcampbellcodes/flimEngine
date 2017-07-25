#include "AudioFileMain.h"
#include "ThreadCommands.h"
#include "VoiceManager.h"
#include "AudioCommandFactory.h"
#include "AudioThreadCommand.h"
#include "SoundManager.h"
void AudioFileMain(CircularData * pIn, CircularData * pOut)
{

	AudioCommandFactory aud = AudioCommandFactory();
	while (!SoundManager::AudioThreadEnded())
	{
		
		ThreadCommand cmd;

		if (pIn->PopFront(cmd) == true) // there is something there!!!! wooooooo
		{
			AudioThreadCommand* audioCommand = aud.Create(cmd.type);
			audioCommand->SetCommand(cmd);
			audioCommand->execute();
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	ThreadCommand cmd;
	cmd.engineState = AudioEngineState::TerminateAudioState;
	pOut->PushBack(cmd);
	

}












/***************************************************************/


/*                       Loading                               */



/***************************************************************/
