#include "PrintSoundCommand.h"
#include "SoundCall.h"
#include "Trace\Trace.h"

PrintSoundCommand::PrintSoundCommand(SoundCall * snd, const char * name) : sound(snd), waveName(name)
{
	this->instant_execute = true;
}

void PrintSoundCommand::execute()
{
	Trace::out("\n---Game Callback\n");
	Trace::out("WaveName: %s\n",waveName);

	int duration = 0;
	float pan = 0.0f;
	this->sound->GetTimeSinceStarted(duration);
	this->sound->GetPan(pan);
	Trace::out("Duration: %d,    HandleID: %x,    Pan: %f\n\n\n", duration, this->sound->GetHandleNo(), pan);
}
