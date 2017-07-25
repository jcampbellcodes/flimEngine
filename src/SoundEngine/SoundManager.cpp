#include "SoundManager.h"
#include "Sound.h"
//#include <xaudio2.h>
#include "AutoXA2Include.h"
#include "BufferManager.h"
#include "SoundList.h"
#include "SoundNode.h"
#include "HashThis.h"
#include "VoiceManager.h"
#include "Timeline.h"
#include "AudioCommand.h"
#include "CallbackManager.h"
#include "SoundEngine.h"
#include "PlaylistManager.h"
#include "AudioFileMain.h"
#include "ThreadHelper.h"
#include "Playlist.h"
#include <xaudio2fx.h>
#include <XAPOFX.h>
#include "SoundManager3D.h"
#include <thread>

#include "AudioCommandTypes\TerminateFileThreadType.h"
#include "AudioCommandTypes\TerminateSoundEngineType.h"


SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
	// necessary for COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	endAudioThread = false;
	list = new SoundList();
	timeline = new Timeline();


	//used to get error codes
	HRESULT hr;

	// COM XAudio2 interface initialized with defaults
	if (FAILED(hr = XAudio2Create(&this->xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR))) {

		printf("error %x", hr);
		//return hr;
	}




	const XAUDIO2_DEBUG_CONFIGURATION dbg = { 1,1,true,true,true,true };
	xAudio2->SetDebugConfiguration(&dbg);

	// master voice initialized
	if (FAILED(hr = this->xAudio2->CreateMasteringVoice(&this->masteringVoice))) {
		printf("error %x", hr);
		//return hr;
	}
	//packing info into struct
	this->masteringVoice->GetVoiceDetails(&this->info.voiceDetails);


	masteringVoice->SetVolume(0.5f);
	/*
	IUnknown * pXAPO;
	CreateFX(__uuidof(FXMasteringLimiter), &pXAPO);
	XAUDIO2_EFFECT_DESCRIPTOR descriptor;
	descriptor.InitialState = true;
	descriptor.OutputChannels = info.voiceDetails.;
	descriptor.pEffect = pXAPO;
	XAUDIO2_EFFECT_CHAIN chain;
	chain.EffectCount = 1;
	chain.pEffectDescriptors = &descriptor;
	masteringVoice->SetEffectChain(&chain);
	pXAPO->Release();
	FXMASTERINGLIMITER_PARAMETERS XAPOParameters = {6, 100};


	masteringVoice->SetEffectParameters(0, &XAPOParameters, sizeof(FXMASTERINGLIMITER_PARAMETERS));
	*/


	// spawn file thread
	this->pF2A = new CircularData();
	assert(pF2A);

	this->pA2F = new CircularData();
	assert(pA2F);

	fileThread = std::thread(AudioFileMain, this->pA2F, this->pF2A);
	SetThreadName(fileThread, "FILE");
	  
	fileThread.detach();


}

SoundManager::~SoundManager()
{
	//CoUninitialize();

	ThreadCommand cmd;
	cmd.type = new TerminateFileThreadType();
	pA2F->PushBack(cmd);

	// wait to hear back and then CUT the line of communication
	ThreadCommand val = ThreadCommand();
	while (val.engineState != AudioEngineState::TerminateAudioState)
	{
		this->pF2A->PopFront(val);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}


	if (pF2A)
	{
		delete pF2A;
	}
	if (pA2F)
	{
		delete pA2F;
	}

	// XAudio2 Unload
	masteringVoice->DestroyVoice();


	xAudio2->Release();

	/*
	// now clean up callback pointers
	while (!this->callbacks.empty())
	{
		delete this->callbacks.top();
		this->callbacks.pop();
	}
	*/

}

snd_err SoundManager::privGetInfo(SoundManagerInfo& out)
{
	out = this->info;
	return snd_err::OK;
}

snd_err SoundManager::privInsertTimelineCommand(AudioCommand * cmd)
{
	snd_err err = snd_err::OK;

	if (cmd)
	{
		this->timeline->Register(cmd, cmd->trigger_time);
	}
	else
	{
		err = snd_err::ERR;
	}

	return err;
}

snd_err SoundManager::privInsertTimelineCommand(AudioCommand * cmd, int trigger_time)
{
	snd_err err = snd_err::OK;

	if (cmd)
	{
		this->timeline->Register(cmd, trigger_time);
	}
	else
	{
		err = snd_err::ERR;
	}

	return err;
}

snd_err SoundManager::privUpdate()
{
	snd_err err = snd_err::OK;
	err = timeline->ProcessAlarms();
	SoundManager3D::Update3DAudio();
	return err;
}

int SoundManager::privGetTime()
{
	return timeline->GetTime();
}

snd_err SoundManager::privEndAudioThread()
{
	snd_err err = snd_err::OK;
	this->endAudioThread = true;
	return err;
}

bool SoundManager::privAudioThreadEnded()
{
	return endAudioThread;
}

snd_err SoundManager::privSendDataF2A(ThreadCommand val)
{
	snd_err err = snd_err::OK;

	this->pF2A->PushBack(val);

	return err;
}

snd_err SoundManager::privSendDataA2F(ThreadCommand val)
{
	snd_err err = snd_err::OK;

	this->pA2F->PushBack(val);

	return err;
}

snd_err SoundManager::GetXAudio2(IXAudio2 *& out)
{
	if (this->xAudio2)
	{
		out = this->xAudio2;
		return snd_err::OK;
	}
	return snd_err::ERR;
}

snd_err SoundManager::privRemove(Sound * snd)
{
	// observer
	// just a cleanup function. snd is about to be deleted, this is called in destructor to fix up lists and ref counting
	// find in list via sound pointer
	SoundNode* node = nullptr;
	list->Find(node, snd);
	assert(node);

	// get md5 and pass it to remove of buffermnager
	BufferManager::Remove(node->data.md5);

	// take off list
	list->Remove(node);

	return snd_err::OK;
}

snd_err SoundManager::privCreateVoice(Track *& v, WAVEFORMATEXTENSIBLE & wfx)
{
	snd_err err = snd_err::OK;
	HRESULT hr;
	v = new Track();
	v->cbMailbox = new CallbackMailbox();
	this->callbacks.push(v->cbMailbox);

	if (FAILED(hr = xAudio2->CreateSourceVoice(&v->voice, (WAVEFORMATEX*)&wfx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, v->cbMailbox /*callback mailbox*/, nullptr, nullptr)))
	{
		// here for breakpoints
		hr;
		err = snd_err::ERR;
	}
	return err;
}

snd_err SoundManager::privLoadSound(std::string key, char* path, void(*cb)(void))
{
	return BufferManager::Add(key.c_str(), (std::string(this->assetPath) + std::string(path)).c_str(), cb);
}

snd_err SoundManager::privLoadSound(unsigned int key, char* path, void(*cb)(void))
{
	return BufferManager::Add(key, (std::string(this->assetPath) + std::string(path)).c_str(), cb);
}

snd_err SoundManager::privPanSound(IXAudio2SubmixVoice *& sourceVoice, X3DAUDIO_DSP_SETTINGS *& dspSettings)
{
	if (!(sourceVoice && dspSettings))
	{
		return snd_err::NULLPTR;
	}

	XAUDIO2_VOICE_DETAILS details;
	sourceVoice->GetVoiceDetails(&details);
	sourceVoice->SetOutputMatrix(this->masteringVoice, details.InputChannels, info.voiceDetails.InputChannels, dspSettings->pMatrixCoefficients);

	return snd_err::OK;
}

snd_err SoundManager::privLoadSound(unsigned int key, const char* path, void(*cb)(void))
{
	return BufferManager::Add(key, (std::string(this->assetPath) + std::string(path)).c_str(), cb);
}

snd_err SoundManager::privUnloadSound(Sound *& snd)
{
	return privRemove(snd);
}

snd_err SoundManager::privCreateChannel(Channel *& out)
{
	// create a submix voice
	snd_err err = snd_err::OK;
	HRESULT hr;
	// create a reverb voice; send dry submix voice to it
	IXAudio2SubmixVoice* s = nullptr;




	
	IUnknown * pReverb;
	hr = XAudio2CreateReverb(&pReverb);
	XAUDIO2_EFFECT_DESCRIPTOR effects = { pReverb, true, 2 };
	XAUDIO2_EFFECT_CHAIN effectChain = { 1, &effects };

	// reverb send
	IXAudio2SubmixVoice* reverbSendVoice = nullptr;
	if (FAILED(hr = xAudio2->CreateSubmixVoice(&reverbSendVoice, 2, 48000, XAUDIO2_VOICE_USEFILTER, 1, nullptr, &effectChain)))
	{
		// here for breakpoints
		hr;
		err = snd_err::ERR;
	}

	XAUDIO2_SEND_DESCRIPTOR reverbSendDesc[2] = 
	{ 
		{ XAUDIO2_SEND_USEFILTER, reverbSendVoice },
		{ 0 , masteringVoice}
	};
	XAUDIO2_VOICE_SENDS reverbSend = { 2, reverbSendDesc };
	
	if (FAILED(hr = xAudio2->CreateSubmixVoice(&s, 1, 48000, XAUDIO2_VOICE_USEFILTER, 0, &reverbSend, nullptr)))
	{
		// here for breakpoints
		hr;
		err = snd_err::ERR;
	}




	// make a new track
	assert(s);
	Channel* t = nullptr;
	t = new Channel(s, reverbSendVoice);
	assert(t);
	// give it to the output pointer
	out = t;

	return err;
}

snd_err SoundManager::privUnload()
{

	// Cancel the timeline!
	if (timeline)
	{
		delete timeline;
		timeline = nullptr;
	}

	/*
	clean sounds/handles
	*/
	if (list)
	{
		delete list;
	}


	/*
		clean buffers
	*/
	BufferManager::Terminate();




	/*
		clean voice manager
	*/
	VoiceManager::Terminate();


	PlaylistManager::Terminate();


	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
	return snd_err::OK;
}



snd_err SoundManager::privGetSound(Sound *& out, std::string key, Playlist* playlist)
{
	XAUDIO2_BUFFER* buffer = nullptr;
	WAVEFORMATEXTENSIBLE* wfx = nullptr;
	snd_err status = BufferManager::Find(key.c_str(), buffer, wfx);
	
	assert(buffer);
	assert(wfx);

	// make a new Sound at the path -- search list
	Sound *newSnd = nullptr;

	newSnd = new Sound(*wfx, buffer, playlist);/* pass in a buffer */

	SoundNode* newNode = new SoundNode(HashThis(key.c_str()), newSnd);
	list->Add(newNode);

	if (!newSnd)
	{
		status = snd_err::ERR;
	}

	out = newSnd;

	status = snd_err::OK;
	return status;
}

snd_err SoundManager::privGetSound(Sound *& out, unsigned int key, Playlist* playlist)
{
	XAUDIO2_BUFFER* buffer = nullptr;
	WAVEFORMATEXTENSIBLE* wfx = nullptr;
	snd_err status = BufferManager::Find(key, buffer, wfx);

	assert(buffer);

	// make a new Sound at the path -- search list
	Sound *newSnd = nullptr;

	newSnd = new Sound(*wfx, buffer, playlist);/* pass in a buffer */

	SoundNode* newNode = new SoundNode(key, newSnd);
	list->Add(newNode);

	if (!newSnd)
	{
		status = snd_err::ERR;
	}

	out = newSnd;

	status = snd_err::OK;
	return status;
}
