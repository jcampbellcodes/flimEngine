#include "TimeManager.h"

FlimTime* FlimTime::instance = nullptr;


FlimTime::FlimTime()
{
	frameTime = 0;
	FrzTime = new FreezeTime();
	previousFrameTime = 0;
	currentFrameTime = Flim::GetTime();
}

FlimTime::~FlimTime()
{

	//DebugMsg::out("Time Cleaned\n");
	if (FrzTime)
	{
		delete FrzTime;
	}

}

void FlimTime::privProcessTime()
{
	previousFrameTime = currentFrameTime;


	//currentFrameTime = Flim::GetTime();
	currentFrameTime = FrzTime->GetTimeInSeconds(Flim::GetTime());

	frameTime = currentFrameTime - previousFrameTime;

	
}

float FlimTime::privTotalTime()
{
	return Flim::GetTime();
}

float FlimTime::privFrameTime()
{
	return frameTime;
}

void FlimTime::privTerminate()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
