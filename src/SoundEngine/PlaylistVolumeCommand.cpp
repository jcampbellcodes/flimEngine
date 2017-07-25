#include "PlaylistVolumeCommand.h"
#include "sndmathtools.h"
#include "SoundManager.h"
#include "Playlist.h"

PlaylistVolumeCommand::PlaylistVolumeCommand(Playlist * snd, float _from, float _to, float t) : playlist(snd), from(_from), to(_to), time(t)
{
	// compute delta
	delta = (std::abs(from - to) * 10) / t;
}

void PlaylistVolumeCommand::execute()
{
	if (playlist)
	{
		if (!nearEqual(from, to))
		{
			lerpFinished = false;
			//PitchFrom = (1 - delta * 2)*PitchFrom + (delta * 2)*PitchTo;
			//PitchFrom = PitchFrom + delta*(PitchTo - PitchFrom);

			if (from > to)
			{
				from -= delta;
			}
			else
			{
				from += delta;
			}

			SoundManager::InsertTimelineCommand(clone(), 10); // no allocation
		}
		else
		{
			from = to;
			lerpFinished = true;
		}
		playlist->Volume(from);
	}
}

PlaylistVolumeCommand * PlaylistVolumeCommand::clone()
{
	return new PlaylistVolumeCommand(*this);
}
