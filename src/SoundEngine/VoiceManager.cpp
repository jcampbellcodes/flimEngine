#include "VoiceManager.h"
#include "HashThis.h"
#include <assert.h>
#include "md5.h"
#include "VoiceFactory.h"
#include "AzulCore.h"


#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

#define MAX_NAME_SIZE 32

VoiceManager* VoiceManager::instance = nullptr;

VoiceManager::VoiceManager() //: activeList(new BufferList()), inactiveList(new BufferList())
{
}


VoiceManager::~VoiceManager()
{
	std::list<VoicePool*>::iterator iter = pools.begin();
	while (iter != pools.end())
	{
		delete (*iter);
		iter++;
	}
	pools.clear();


	//DebugMsg::out("VoiceManager cleaned\n");
	/*
	if (activeList)
	{
		delete activeList;
	}
	if (inactiveList)
	{
		delete inactiveList;
	}
	*/
}




/***************************************************************/


/*                  Private Implementation                     */


/***************************************************************/

snd_err VoiceManager::privSubmitFactory(WAVEFORMATEXTENSIBLE& wfx)
{
	// sound manager just loaded a sound and checks to see if the format has been created yet
	snd_err err = snd_err::OK;
	
	unsigned int md5 = HashThis(wfx);

	std::list<VoicePool*>::iterator iter = pools.begin();
	while (iter != pools.end())
	{
		if (md5 == (*iter)->format)
		{
			// it's already there!
			return snd_err::MULTIPLE_ADD;
		}
		iter++;
	}
	// if you got here, this format wasn't created yet
	// make it
	VoicePool* newPool = new VoicePool();
	newPool->format = md5;
	newPool->voices = new VoiceFactory(wfx);

	// add it to the list
	pools.push_back(newPool);

	return err;
}

snd_err VoiceManager::privGetVoice(Track*& out, WAVEFORMATEXTENSIBLE& wfx, int priority, Sound* snd)
{
	snd_err err = snd_err::OK;

	// sound manager just asked for a voice
	unsigned int md5 = HashThis(wfx);
	VoiceFactory* factory = nullptr;
	// hash wfx to unsigned int and search through list to see if it is found
	// if not, return err. all should have been created upon load
	std::list<VoicePool*>::iterator iter = pools.begin();

	while (iter != pools.end())
	{
		if (md5 == (*iter)->format)
		{
			// alright let's go!
			factory = (*iter)->voices;
			break;
		}
		iter++;
	}




	if (!factory)
	{
		VoiceManager::SubmitFactory(wfx);


		iter = pools.begin();

		while (iter != pools.end())
		{
			if (md5 == (*iter)->format)
			{
				// alright let's go!
				factory = (*iter)->voices;
				break;
			}
			iter++;
		}


		//err = snd_err::NOT_FOUND;
		//return err;
	}
	assert(factory);
	//it has been found, now ask the factory for a voice
	err = factory->GetVoice(out, priority, snd);

	//assert(out);

	return err;
}

snd_err VoiceManager::privReturnVoice(Track*& ret, WAVEFORMATEXTENSIBLE& wfx)
{
	snd_err err = snd_err::OK;

	// sound manager just asked for a voice
	unsigned int md5 = HashThis(wfx);
	VoiceFactory* factory = nullptr;
	// hash wfx to unsigned int and search through list to see if it is found
	// if not, return err. all should have been created upon load
	std::list<VoicePool*>::iterator iter = pools.begin();
	while (iter != pools.end())
	{
		if (md5 == (*iter)->format)
		{
			// alright let's go!
			factory = (*iter)->voices;
			break;
		}
		iter++;
	}
	assert(factory);
	if (!factory)
	{
		err = snd_err::NOT_FOUND;
		return err;
	}

	//it has been found, now ask the factory for a voice
	err = factory->ReturnVoice(ret);

	assert(err != snd_err::ERR);

	return err;
}

snd_err VoiceManager::privTerminate()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
	return snd_err::OK;
}



snd_err VoiceManager::privFind(Track *& out, WAVEFORMATEXTENSIBLE& wfx)
{
	out;
	wfx;
	return snd_err::OK;
}




snd_err VoiceManager::Find(BufferNode *& out, unsigned int md5)
{
	out;
	md5;
	return snd_err::ERR;
}