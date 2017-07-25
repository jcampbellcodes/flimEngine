#include "SoundCallPrintDurationCommand.h"
#include "SoundCall.h"
#include "Trace\Trace.h"

SoundCallPrintDuration::SoundCallPrintDuration(SoundCall * snd, const char* waveName) : soundCall(snd), name(waveName)
{
}

void SoundCallPrintDuration::execute()
{
	Trace::out("\n");
	int time;
	soundCall->GetTimeSinceStarted(time);
	Trace::out("%s -- Duration: %dms\n", name, time);
}
