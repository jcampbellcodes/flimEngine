#include "VolumeCommand.h"
#include "SoundManager.h"
#include "sndmathtools.h"
#include <stdio.h>


VolumeCommand::VolumeCommand(Sound * snd, float from, float to, float t) : AudioCommand(snd), VolumeFrom(from), VolumeTo(to), time(t)
{
}

VolumeCommand::VolumeCommand(float from, float to, float time) : VolumeFrom(from), VolumeTo(to), time(time)
{
}



VolumeCommand * VolumeCommand::clone()
{
	return new VolumeCommand(*this);
}

void VolumeCommand::execute()
{
	if (sound)
	{
		if (!nearEqual(VolumeFrom, VolumeTo))
		{

			lerpFinished = false;
			//VolumeFrom = (1 - time)*VolumeFrom + time*VolumeTo;
			VolumeFrom = (VolumeFrom + time*(VolumeTo - VolumeFrom));

			//SoundManager::InsertTimelineCommand(this, 0); // no allocation
		}
		else
		{
			VolumeFrom = VolumeTo;
			lerpFinished = true;
		}
		//DebugMsg::out("Volumefrom:%f\n", VolumeFrom);
		sound->Volume(VolumeFrom);
	}
}