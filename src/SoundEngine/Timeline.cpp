#include "Timeline.h"
//#include "../Game.h"
#include "AudioCommand.h"
#include "Trace\Trace.h"


/*

make a list with time nodes

each node has a stack of commands and a time value

when adding a command, look for a time value equal to yours, and if it doesn't exist, create one

no need for multimap

*/

Timeline::Timeline()
{
	Timer;
	timer.tic();
}

Timeline::~Timeline()
{
	
	std::multimap<int, AudioCommand*>::iterator iter = timeline.begin();

	while (iter != timeline.end())
	{
		AudioCommand* toDelete = (*iter).second;

		//timeline.erase((*iter).second->deleteIter);
		delete toDelete;
		// check if there are more commands on this
		iter++;
	}
	

	Trace::out("Timeline cleaned!\n");
}

// t is time in milliseconds
snd_err Timeline::Register(AudioCommand* cmd, int t)
{
	const Time elapsedTime = timer.toc();
	int total_time_ms = Time::quotient(elapsedTime, Time(TIME_ONE_MILLISECOND));
	// add alarmable to the map with t as a time
	
	// add the time to offset
	int offsetTime = 0;
	if (t)
	{
		offsetTime = total_time_ms + t;
	}
	

	cmd->deleteIter = timeline.insert(std::pair<int, AudioCommand*>(offsetTime, cmd));

	return snd_err::OK;
}

snd_err Timeline::Deregister(AudioCommand* cmd)
{
	timeline.erase(cmd->deleteIter);
	/*
	// use iterator to remove
	if (cmd->lerpFinished)
	{
		// find command
		timeline.erase(cmd->deleteIter);

		//delete cmd; // playlist owns commands. it should delete them
	}
	else
	{
		timeline.erase(cmd->deleteIter);
		this->Register(cmd, 10);
		return snd_err::IN_USE;
	}
	*/
	return snd_err::OK;
}

snd_err Timeline::RemovePlaylist(unsigned int instance)
{
	snd_err err = snd_err::OK;

	std::multimap<int, AudioCommand*>::iterator iter = timeline.begin();
	std::multimap<int, AudioCommand*>::iterator iterDelete = timeline.begin();
	while (iter != timeline.end())
	{
		// erase all commands with the given instance
		if (instance == (*iter).second->GetID())
		{
			iterDelete = iter;
			iter++;
			timeline.erase(iterDelete);
		}
		else
		{
			iter++;
		}


	}

	return err;
}

int Timeline::GetTime()
{
	const Time elapsedTime = timer.toc();
	return Time::quotient(elapsedTime, Time(TIME_ONE_MILLISECOND));
}

snd_err Timeline::ProcessAlarms()
{
	// get system time
	// see if first entry in map's key is <= Flim::TimeInSeconds

	// for now, deregister here
	// cannot dereference last iter
	// while iter >= system time, call trigger alarm

	std::multimap<int, AudioCommand*>::iterator iter = timeline.begin();
	const Time elapsedTime = timer.toc();
	int total_time_ms = Time::quotient(elapsedTime, Time(TIME_ONE_MILLISECOND));
	int time = total_time_ms;

	while (iter != timeline.end() && (iter->first <= time))
	{
		// execute the commands
		(*iter).second->execute();
		this->Deregister((*iter).second);

		// check if there are more commands on this
		iter = timeline.begin();
	}

	return snd_err::OK;
}
