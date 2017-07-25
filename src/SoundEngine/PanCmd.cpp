#include "PanCmd.h"
#include "SoundManager.h"
#include "sndmathtools.h"
#include "AssignCallbackCommand.h"

PanCommand::PanCommand(Sound * snd, float from, float to, float t) : AudioCommand(snd), panFrom(from), panTo(to), time(t)
{ 
}

PanCommand::PanCommand(float from, float to, float t) : panFrom(from), panTo(to), time(t)
{
	delta = (std::abs(from - to) * 10) / t;
}

void PanCommand::execute()
{
	if (sound)
	{
		if (!nearEqual(panFrom, panTo))
		{
			lerpFinished = false;
			//panFrom = (1 - time)*panFrom + time*panTo;
			//panFrom = panFrom + time*(panTo - panFrom);
			if (panFrom > panTo)
			{
				panFrom -= delta;
			}
			else
			{
				panFrom += delta;
			}

			SoundManager::InsertTimelineCommand(clone(), 10); // no allocation
		}
		else
		{
			panFrom = panTo;
			lerpFinished = true;
		}
		//DebugMsg::out("panfrom:%f\n", panFrom);
		sound->Pan(panFrom);
	}
}

PanCommand * PanCommand::clone()
{
	return new PanCommand(*this);
}
