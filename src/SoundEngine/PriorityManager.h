#pragma once
#ifndef PRIORITYMANAGER_H
#define PRIORITYMANAGER_H


#define MAX_NUM_SOUND_CALLS 10000

#include "snd_err.h"
#include "Timer.h"
#include "PrintPriorityCommand.h"

class SoundCall;
class Timeline;
class AudioCommand;

class PriorityManager
{
public:
	//big four
	PriorityManager();
	~PriorityManager();


	PriorityManager(const PriorityManager&) = delete;
	PriorityManager& operator=(const PriorityManager&) = delete;

	//singleton
	static PriorityManager* instance;
	static PriorityManager& Instance()
	{
		if (!instance)
		{
			instance = new PriorityManager();
		}
		return *instance;
	}

	//static methods
	
	// add sound(SoundCall*)
	static snd_err AttemptToPlay(SoundCall* snd, int& priorityIndex)
	{
		return Instance().privRegisterSound(snd, priorityIndex);
	}

	static snd_err AddSound(SoundCall* snd, int& priorityIndex, int time)
	{
		return Instance().privAddSound(snd, priorityIndex, time);
	}

	static snd_err AddCommand(AudioCommand* cmd, int time)
	{
		return Instance().privAddCommand(cmd, time);
	}

	// remove sound(index)
	static snd_err RemoveSound(int index)
	{
		return Instance().privRemoveSound(index);
	}

	// terminate
	static snd_err Terminate()
	{
		return Instance().privTerminate();
	}

	static snd_err Print(int time)
	{
		return Instance().privAddCommand(new PrintPriorityCommand(), time);
	}

	//print table
	static snd_err PrintAll()
	{
		return Instance().privPrintAll();
	}

	static snd_err CurrentActiveSounds(int& out)
	{
		return Instance().privActiveSounds(out);
	}

	static snd_err Update()
	{
		return Instance().privUpdate();
	}

private:
	SoundCall* priorityTable[MAX_NUM_SOUND_CALLS];
	int activeSounds;

	snd_err privActiveSounds(int& out);

	// add sound(SoundCall*)
	snd_err privRegisterSound(SoundCall*, int&);

	snd_err privAddSound(SoundCall*, int& priorityIndex, int time);

	snd_err privAddCommand(AudioCommand*, int time);

	// remove sound(index)
	snd_err privRemoveSound(int index);

	snd_err privUpdate();

	// terminate
	snd_err privTerminate();

	Timeline* playCommands;

	//print table
	snd_err privPrintAll();

};

#endif