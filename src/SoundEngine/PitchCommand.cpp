#include "PitchCommand.h"
#include "SoundManager.h"
#include "sndmathtools.h"

PitchCommand::PitchCommand(Sound * snd, float from, float to, float t) : AudioCommand(snd), PitchFrom(from), PitchTo(to), time(t)
{
}

PitchCommand::PitchCommand(float from, float to, float t) : PitchFrom(from), PitchTo(to), time(t)
{
	// 10 is the re-add time for the timer. Make this less arbitrary, eh?
	delta = (std::abs(from - to) * 10) / t;
}

void PitchCommand::execute()
{
	if (sound)
	{
		if (!nearEqual(PitchFrom, PitchTo))
		{
			lerpFinished = false;
			//PitchFrom = (1 - delta * 2)*PitchFrom + (delta * 2)*PitchTo;
			//PitchFrom = PitchFrom + delta*(PitchTo - PitchFrom);

			if (PitchFrom > PitchTo)
			{
				PitchFrom -= delta;
			}
			else
			{
				PitchFrom += delta;
			}

			SoundManager::InsertTimelineCommand(clone(), 10); // no allocation
		}
		else
		{
 			PitchFrom = PitchTo;
			lerpFinished = true;
		}
		//DebugMsg::out("Pitchfrom:%f\n", PitchFrom);
		sound->Pitch(PitchFrom);
	}
}

PitchCommand * PitchCommand::clone()
{
	return new PitchCommand(*this);
}

