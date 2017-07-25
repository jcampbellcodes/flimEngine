#include "VoiceFactory.h"
#include "VoiceManager.h"
#include "SoundManager.h"
#include <assert.h>
#include "Sound.h"

#include "Timer.h"

#include <thread>

Track::~Track()
{



	if (voice)
	{
		voice->DestroyVoice();
		voice = nullptr;
	}

	// weird multithreading issue
	if (cbMailbox)
	{
		//cbMailbox->Terminate();
		delete cbMailbox;
		cbMailbox = nullptr;
	}


	if (currentSound)
	{
		//delete currentSound;
		currentSound = nullptr;
	}
}

VoiceFactory::VoiceFactory(WAVEFORMATEXTENSIBLE & wfx) : format(wfx)
{
	// make a ton of new voices in the inactive pool
	unsigned int i = 0;
	while (i < DEFAULT_NUM_VOICES)
	{
		// make a new voice object
		Track* v = nullptr;

		// tell xaudio to create a voice there
		SoundManager::CreateVoice(v, format);

		// add voice to inactive list
		inactivePool.insert(v);

		i++;
	}
}

VoiceFactory::~VoiceFactory()
{
	
	std::set<Track*>::iterator inactiveIter = inactivePool.begin();
	int i = 0;
	while (inactiveIter != inactivePool.end())
	{

		//inactivePool.top()->voice = nullptr;
		//inactivePool.top()->cbMailbox->Terminate();
		//inactivePool.top()->voice->DestroyVoice();
		i++;
		//(*inactiveIter)->voice->DestroyVoice();
		delete (*inactiveIter);
		//inactivePool.erase(inactiveIter);
		inactiveIter++;
	}
	// clean up all the voices
	
	
	std::list<Track*>::iterator iter = activePool.begin();
 	while (iter != activePool.end())
	{
		delete (*iter);
		//(*iter)->voice->DestroyVoice();
		//(*iter)->cbMailbox->Terminate();
		//delete (*iter)->cbMailbox;
		//(*iter)->cbMailbox = nullptr;
		iter++;
	}
	activePool.clear();
	
	

	//DebugMsg::out("VoiceFactory cleaned\n");
}

snd_err VoiceFactory::GetVoice(Track *& out, int priority, Sound* sound)
{
	snd_err err = snd_err::OK;
	// make output variable
	Track* newVoice = nullptr;


	if (!inactivePool.empty()) // there are unused voices! Hooray!
	{
		newVoice = *inactivePool.begin();
		newVoice->currentSound = sound;
		newVoice->currentPriority = priority;
		newVoice->startTime = SoundManager::GetSoundTime();
		inactivePool.erase(inactivePool.begin());

		// push the new guy to the active pool
		activePool.push_front(newVoice);

	}
	else // there are no unused voices... search active pool to see if we can take an active track with lower priority
	{
		// checks both priority and lifetime of active tracks to see if we can boot someone out
		//if (AuditTracks(newVoice, priority, sound) == snd_err::NO_TRACK) return snd_err::NO_TRACK;
		//SoundManager::CreateVoice(newVoice, format);
		//activePool.push_front(newVoice);
		err = snd_err::NO_TRACK;
		return err;
	}
	assert(newVoice);
	if (!newVoice)
	{
		err = snd_err::NULLPTR;
	}
	// assert
	assert(newVoice);
	out = newVoice;
	//DebugMsg::out("voice given out: %u\n", out);

	return err;
}

snd_err VoiceFactory::ReturnVoice(Track *& in)
{
	snd_err err = snd_err::OK;
	
	//DebugMsg::out("voice returned: %u\n", in);
	activePool.remove(in);
	inactivePool.insert(in);

	return err;
}


// The gunky edge case that happens if a sound is right on the threshold of not being able to be played
// Ie -- all tracks are full but this sound is REALLY important,
// Or (God Forbid) -- it is equally as important as several other voices and you are going to decide which voice is old enough to die
snd_err VoiceFactory::AuditTracks(Track *& newVoice, int priority, Sound * sound)
{
	snd_err err = snd_err::OK;

	std::list<Track*>::iterator iter = activePool.begin();
	std::list<Track*> equalPriority;
	while (iter != activePool.end())
	{
		// see if there is an active voice with lower priority
		if ((*iter)->currentPriority > priority)
		{

			newVoice = (*iter);

			// tell the other guy he is VOICE-less
			newVoice->voice->FlushSourceBuffers();
			newVoice->currentSound->ClearTrack();


			newVoice->currentSound = sound;
			newVoice->currentPriority = priority;
			break;
		}
		else if ((*iter)->currentPriority == priority) // squirrel away those with equal priority in case everything else is booked up
		{
			equalPriority.push_back(*iter);
		}
		iter++;
	}

	if (!newVoice)
	{
		if (!equalPriority.empty()) // it didn't work! try going through and seeing if the list of equals has a long lifetime
		{
			std::list<Track*>::iterator iterEqual = equalPriority.begin();
			int longestLifetime = 0;
			int currentLifetime;
			Track* oldestTrack = nullptr;
			while (iterEqual != equalPriority.end())
			{
				currentLifetime = SoundManager::GetSoundTime() - (*iterEqual)->startTime;
				if (currentLifetime > longestLifetime)
				{
					longestLifetime = currentLifetime;
					oldestTrack = (*iterEqual);
				}
				iterEqual++;
			}
			assert(oldestTrack);
			// after this, the oldest track will be found
			newVoice = oldestTrack;

			// tell the other guy he is VOICE-less
			newVoice->voice->FlushSourceBuffers();
			newVoice->currentSound->ClearTrack();


			newVoice->currentSound = sound;
			newVoice->currentPriority = priority;

		}
		if (!newVoice)
		{
			err = snd_err::NO_TRACK;
		}
	}
	return err;
}

