#include <thread>
#include <assert.h>

#include "AudioThreadCommand.h"
#include "AudioCommandFactory.h"
#include "AudioMain.h"
#include "SoundManager.h"

void AudioMain(CircularData *pIn, CircularData * pOut)
{


	AudioCommandFactory aud = AudioCommandFactory();
	
    while (!SoundManager::AudioThreadEnded())
	{
		SoundManager::Update();
		
		ThreadCommand cmd;

		if (pIn->PopFront(cmd) == true) // there is something there!!!! wooooooo
		{
			AudioThreadCommand* audioCommand = aud.Create(cmd.type);

			audioCommand->SetCommand(cmd);

			audioCommand->execute();

			// I'm going to live with this for now -->
			// Much better than 30+ case switch statement called once every audio frame
			// (by the way 1 audio frame == 16 game frames)
			// I'm sure the fix is easy but the engine was due 50 min ago ;)
			//delete cmd.type;
		}

		SoundManager::Update();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(1));




	}

	SoundManager::Unload();

	ThreadCommand end;
	end.engineState = AudioEngineState::TerminateAudioState;
	pOut->PushBack(end);

#ifdef _USE_TRACE_NEW
	//_CrtDumpMemoryLeaks();
#endif



}