#include "TransitionOnEnd.h"
#include "Sound.h"
#include "Trace\Trace.h"
TransitionOnEnd::~TransitionOnEnd()
{
}
TransitionOnEnd::TransitionOnEnd(Sound * _stop, Sound * _start)
{
	sound = _stop;
	secondarySound = _start;
	commandType = CMDTYPES::BUFFER_END;
	instant_execute = true;
}

TransitionOnEnd::TransitionOnEnd()
{
	commandType = CMDTYPES::BUFFER_END;
	instant_execute = true;
	waveName = "";
}

TransitionOnEnd::TransitionOnEnd(const char* name)
{
	commandType = CMDTYPES::BUFFER_END;
	instant_execute = true;
	int i = 0;
	waveName = new char[sizeof(name)];
	while (i < sizeof(name))
	{
		waveName[i] = name[i];
		i++;
	}
	waveName[i] = '\0';
}

void TransitionOnEnd::execute()
{
	if (sound && secondarySound)
	{
		sound->Stop();
		secondarySound->Play();
		Trace::out("\n\nSwitch to:\n");
		Trace::out(waveName);
		Trace::out("\n\n\n");
	}
}

TransitionOnEnd * TransitionOnEnd::clone()
{
	return new TransitionOnEnd(*this);
}
