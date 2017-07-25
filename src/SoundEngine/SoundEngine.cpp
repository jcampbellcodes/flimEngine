#include <assert.h>

#include "Trace\Trace.h"
#include "SoundEngine.h"
#include "ThreadHelper.h"
#include "AudioMain.h"
#include "SoundManager.h"
#include "TerminateSoundEngineCommand.h"
#include "SoundManager.h"
#include "PriorityManager.h"

#include "AudioCommandTypes\InitializeScriptType.h"
#include "AudioCommandTypes\InitializeSoundType.h"
#include "AudioCommandTypes\TerminateFileThreadType.h"
#include "AudioCommandTypes\TerminateSoundEngineType.h"

SoundEngine *SoundEngine::instance = nullptr;

SoundEngine::SoundEngine()
{

}

SoundEngine::~SoundEngine()
{
	

	std::map<unsigned int, SoundCall*>::iterator iter = this->activeSoundCalls.begin();
	while (iter != activeSoundCalls.end())
	{
		delete (*iter).second;
		iter++;
	}
	activeSoundCalls.clear();


	
	if (this->pA2GBuff)
	{
		delete pA2GBuff;
	}
	
	if (this->pG2ABuff)
	{
		delete pG2ABuff;
	}
	

}

snd_err SoundEngine::privCreateSoundCall(SoundCall *& in, SoundCallID id, int priority)
{
	snd_err err = snd_err::OK;

	in = new SoundCall(id, priority);

	this->activeSoundCalls.insert(std::pair<unsigned int, SoundCall*>(in->GetHandleNo(), in));

	return err;
}

snd_err SoundEngine::privCreateSoundCall(SoundCall *& in, SoundCallID id, bool is3D)
{
	snd_err err = snd_err::OK;

	in = new SoundCall(id, is3D);

	this->activeSoundCalls.insert(std::pair<unsigned int, SoundCall*>(in->GetHandleNo(), in));

	return err;
}

snd_err SoundEngine::privFindSoundCall(SoundCall*& out, unsigned int handle)
{
	snd_err err = snd_err::OK;

	out = this->activeSoundCalls.at(handle);

	return err;
}

snd_err SoundEngine::privLoadScript(std::string path, SoundCallID id, void(*cb)(void) = nullptr)
{
	snd_err err = snd_err::OK;

	ThreadCommand cmd;
	cmd.type = new InitializeScriptType();
	std::string str = "Sounds\\Scripts\\";
	str.append(path);
	cmd.scriptPath = str;
	cmd.id = id;
	cmd.loadedCallback = cb;

	this->privSendData(cmd);

	return err;
}

snd_err SoundEngine::privLoadSound(std::string path, SoundCallID id, void(*cb)(void))
{
	snd_err err = snd_err::OK;

	ThreadCommand cmd;
	cmd.type = new InitializeSoundType();
	cmd.scriptPath = path;
	cmd.id = id;
	cmd.loadedCallback = cb;

	this->privSendData(cmd);

	return err;
}

CircularData * SoundEngine::privGetG2ABuff()
{
	return this->pG2ABuff;
}

CircularData * SoundEngine::privGetA2GBuff()
{
	return this->pA2GBuff;
}

snd_err SoundEngine::privSendData(ThreadCommand data)
{
	snd_err err = snd_err::OK;
	//Trace::out("Game->Audio: %x \n", data);
	this->pG2ABuff->PushBack(data);
	return err;
}

snd_err SoundEngine::privSendDataA2G(ThreadCommand data)
{
	snd_err err = snd_err::OK;
	//Trace::out("Audio->Game: %x \n", data);
	this->pA2GBuff->PushBack(data);
	return err;
}

snd_err SoundEngine::privUpdate()
{
	snd_err err = snd_err::OK;

	PriorityManager::Update();

	ThreadCommand val;

	if (this->pA2GBuff->PopFront(val) == true)
	{
		//val->execute();
	}
	return err;
}


snd_err SoundEngine::privCreate()
{
	snd_err err = snd_err::OK;
	this->pG2ABuff = new CircularData();
	assert(pG2ABuff);

	this->pA2GBuff = new CircularData();
	assert(pA2GBuff);

	SetMainThreadName("GAME");
	audioThread = std::thread(AudioMain, this->pG2ABuff, this->pA2GBuff);
	SetThreadName(audioThread, "AUDIO");
	
	audioThread.detach();


	return err;
}


snd_err SoundEngine::privTerminate()
{
	//SoundManager::Unload();
	ThreadCommand cmd;
	cmd.type = new TerminateSoundEngineType();
	this->privSendData(cmd);


	ThreadCommand val = ThreadCommand();
	while (val.engineState != AudioEngineState::TerminateAudioState)
	{
		this->pA2GBuff->PopFront(val);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	
	PriorityManager::Terminate();

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
	


	return snd_err::OK;
}
