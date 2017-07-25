#include "PriorityManager.h"
#include "SoundCall.h"
#include "Trace\Trace.h"
#include "MarkForPlayCommand.h"
#include "SoundEngine.h"
#include "Timeline.h"
#include <list>

PriorityManager* PriorityManager::instance = nullptr;

PriorityManager::PriorityManager()
{
	activeSounds = 0;
	int i = 0;
	while (i < MAX_NUM_SOUND_CALLS)
	{
		priorityTable[i] = nullptr;
		i++;
	}

	this->playCommands = new Timeline();
}

PriorityManager::~PriorityManager()
{
	if (playCommands)
	{
		delete playCommands;
	}
}

snd_err PriorityManager::privActiveSounds(int & out)
{
	snd_err err = snd_err::OK;

	out = this->activeSounds;

	return err;
}

snd_err PriorityManager::privRegisterSound(SoundCall * snd, int& outIndex)
{
	snd_err err = snd_err::ERR;
	if (!snd)
	{
		err = snd_err::NULLPTR;
		return err;
	}

	int firstPass = 0;
	while (firstPass < MAX_NUM_SOUND_CALLS)
	{
		if (!priorityTable[firstPass])
		{
			// here's where i'm putting you
			outIndex = firstPass;
			//huzzah we are good
			priorityTable[firstPass] = snd;
			err = snd_err::OK;
			this->activeSounds++;
			return err;
		}
		firstPass++;
	}



	int priority = 1000;      // 0 would be misleading
	int soundPriority = 1000; // 0 would be misleading
	snd->GetPriority(soundPriority);
	int i = 0;
	std::list<SoundCall*> samePriority;
	while (i < MAX_NUM_SOUND_CALLS)
	{
		priorityTable[i]->GetPriority(priority);
		if (priority > soundPriority)
		{
			// here's where i'm putting you
			outIndex = i;
			//huzzah we are good
			// kill em
			priorityTable[i]->Stop();

			priorityTable[i] = snd;
			err = snd_err::OK;
			return err;
		}
		else if (soundPriority == priority) // they are the same... squirrel them away just in case.
		{
			samePriority.push_back(priorityTable[i]);
		}
		i++;
	}

	// if you made it here, you might have a problem...
	if (samePriority.size())
	{
		std::list<SoundCall*>::iterator iter = samePriority.begin();
		int oldestTime = 0;
		int residentSoundTime = 0;

		SoundCall* oldestSoundCall = nullptr;
		while (iter != samePriority.end())
		{
			(*iter)->GetTimeSinceStarted(residentSoundTime);
			if (residentSoundTime > oldestTime)
			{
				oldestTime = residentSoundTime;
				oldestSoundCall = (*iter);
			}
			iter++;
		}
		// we now know the oldest sound by brute force
		assert(oldestSoundCall);
		int index = 0;
		oldestSoundCall->GetPriorityIndex(index);
		oldestSoundCall->Stop();
		priorityTable[index] = snd;
		err = snd_err::OK;
		return err;

	}
		// if you made it past here, your priority is too low

	/*
	if (activeSounds < MAX_NUM_SOUND_CALLS) // there is an open slot! go find it
	{
		int i = 0;
		while (i < MAX_NUM_SOUND_CALLS)
		{
			if (!priorityTable[i])
			{
				// here's where i'm putting you
				outIndex = i;
				//huzzah we are good
				priorityTable[i] = snd;
				err = snd_err::OK;
				this->activeSounds++;
				return err;
			}
			i++;
		}
		// something is funky
		assert(false);
		err = snd_err::ERR;
		return err;
	}
	else // go through list and both add sounds of the same priority to a vector and see if there is a sound with less priority
	{
		int priority = 1000;      // 0 would be misleading
		int soundPriority = 1000; // 0 would be misleading
		snd->GetPriority(soundPriority);
		int i = 0;
		std::list<SoundCall*> samePriority;
		while (i < MAX_NUM_SOUND_CALLS)
		{
			priorityTable[i]->GetPriority(priority);
			if (priority > soundPriority)
			{
				// here's where i'm putting you
				outIndex = i;
				//huzzah we are good
				// kill em
				priorityTable[i]->Stop();

				priorityTable[i] = snd;
				err = snd_err::OK;
				return err;
			}
			else if (soundPriority == priority) // they are the same... squirrel them away just in case.
			{
				samePriority.push_back(priorityTable[i]);
			}
			i++;
		}

		// if you made it here, you might have a problem...
		if (samePriority.size())
		{
			std::list<SoundCall*>::iterator iter = samePriority.begin();
			int oldestTime = 0;
			int residentSoundTime = 0;

			SoundCall* oldestSoundCall = nullptr;
			while (iter != samePriority.end())
			{
				(*iter)->GetTimeSinceStarted(residentSoundTime);
				if (residentSoundTime > oldestTime)
				{
					oldestTime = residentSoundTime;
					oldestSoundCall = (*iter);
				}
				iter++;
			}
			// we now know the oldest sound by brute force
			assert(oldestSoundCall);
			int index = 0;
			oldestSoundCall->GetPriorityIndex(index);
			oldestSoundCall->Stop();
			priorityTable[index] = snd;
			err = snd_err::OK;
			return err;
		}

		// if you made it past here, your priority is too low
	}
	*/
	
	return err;
}

snd_err PriorityManager::privAddSound(SoundCall * toAdd, int& priorityIndex, int time)
{
	MarkForPlayCommand* markForPlay = new MarkForPlayCommand(toAdd, priorityIndex);
	this->playCommands->Register(markForPlay, time);
	return snd_err::OK;
}

snd_err PriorityManager::privAddCommand(AudioCommand * cmd, int time)
{
	this->playCommands->Register(cmd, time);
	return snd_err::OK;
}

snd_err PriorityManager::privRemoveSound(int index)
{
	snd_err err = snd_err::OK;

	priorityTable[index] = nullptr;
	this->activeSounds--;

	return err;
}

snd_err PriorityManager::privTerminate()
{
	snd_err err = snd_err::OK;

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}

	return err;
}

snd_err PriorityManager::privPrintAll()
{
	snd_err err = snd_err::OK;
	int iter = 0;
	unsigned int curHandle = 0;
	int curLifetime = 0;
	int priority = 0;
	Trace::out("\n---------------------ACTIVE SOUND CALLS--------------------------\n");

	int counter = 0;
	while (iter < MAX_NUM_SOUND_CALLS)
	{
		if (priorityTable[iter])
		{
			curHandle = priorityTable[iter]->GetHandleNo();
			priorityTable[iter]->GetTimeSinceStarted(curLifetime);
			priorityTable[iter]->GetPriority(priority);

			Trace::out("\nHandle: %x | Priority: %d | Lifetime %d\n", curHandle, priority, curLifetime);
			counter++;
		}
		iter++;
	}
	if (!counter)
	{
		Trace::out("\n-------------No Active Sounds----------------\n");
	}
	Trace::out("\n-----------------------------------------------\n");
	return err;
}

snd_err PriorityManager::privUpdate()
{
	this->playCommands->ProcessAlarms();
	return snd_err::OK;
}
