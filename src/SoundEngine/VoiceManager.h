#pragma once
#ifndef VoiceManager_H
#define VoiceManager_H

#include "snd_err.h"
//#include <xaudio2.h>
#include "AutoXA2Include.h"
#include "Manager.h"
#include "List.h"
#include "BufferNode.h"
#include "VoiceFactory.h"

#include <list>

/*

Callback Manager
-- singleton that has several registration brokers, one for each xaudio event


-- has a private callback method pointer that the voice manager has access to and uses to initialize voices


-- commands are submitted by audiosources to the callback manager (maybe with an enum as a parameter for the callback type), who 
   adds them to the correct broker. Two submission methods: SubmitInstantCommand(Command*) and SubmitDeferredCommand(Command*)


-- commands in the callback brokers stay for the entire life of a sound. it is a sound's responsibility to remove commands on its death


-- internally inside the xaudio2 callback object, the broker fires two methods : ProcessInstantCommands(); and ProcessDeferredCommands();
-- instant commands are execute()'d immediately, for commands that NEED to be instant, like a sample accurate transition
-- deferred commands are commands that you don't know how long they will take and will be detrimental in a blocking call
-- deferred commands sent to the timer class with a time of 0 so they will be process with the other commands in the timer process loop

*/



class VoiceFactory;

struct VoicePool
{
	VoicePool() = default;
	VoicePool(const VoicePool&) = default;
	VoicePool& operator=(const VoicePool&) = default;
	~VoicePool()
	{
		if (voices)
		{
			delete voices;
			voices = nullptr;
		}
	}


	// format
	unsigned int format;
	// voice pool
	VoiceFactory* voices = nullptr;
};

class VoiceManager 
{
private:
	//big four and singleton
	VoiceManager();
	~VoiceManager();
	VoiceManager(const VoiceManager&) = delete;
	VoiceManager& operator=(const VoiceManager&) = delete;

	static VoiceManager* instance;
	static VoiceManager& Instance()
	{
		if (!instance)
		{
			instance = new VoiceManager();
		}
		return *instance;
	}

	// Pooling!
	// Linked list of voice pools
	// whenever a new format is requested, add it and create a pool of voices for it


	// when a sound needs a voice, it passes a pointer to the pool it wants.
	std::list<VoicePool*> pools;


	snd_err Load(WAVEFORMATEXTENSIBLE& _wfx, XAUDIO2_BUFFER& out, const char* path);
	// internal find
	snd_err Find(BufferNode*& out, unsigned int md5);

	snd_err privSubmitFactory(WAVEFORMATEXTENSIBLE & wfx);


	// takes in a string and then hashes md5
	snd_err privGetVoice(Track *& out, WAVEFORMATEXTENSIBLE & wfx, int priority, Sound* snd);


	// return an active voice to the inactive list
	snd_err privReturnVoice(Track*& ret, WAVEFORMATEXTENSIBLE& wfx);

	// takes a string key and output pointer reference
	snd_err privFind(Track*& out, WAVEFORMATEXTENSIBLE& wfx);

	// destroy all the voices
	snd_err privTerminate();

public:

	// outputs a voice, input a 
	static snd_err GetVoice(Track*& out, WAVEFORMATEXTENSIBLE& wfx, int priority, Sound* snd)
	{
		return Instance().privGetVoice(out, wfx, priority, snd);
	}

	// takes in the string and hashes md5
	static snd_err ReturnVoice(Track*& ret, WAVEFORMATEXTENSIBLE& wfx)
	{
		return Instance().privReturnVoice(ret, wfx);
	}

	static snd_err Terminate()
	{
		return Instance().privTerminate();
	}

	static snd_err SubmitFactory(WAVEFORMATEXTENSIBLE & wfx)
	{
		return Instance().privSubmitFactory(wfx);
	}


};


#endif // 
