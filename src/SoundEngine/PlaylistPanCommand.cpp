#include "PlaylistPanCommand.h"
#include "sndmathtools.h"
#include "SoundManager.h"
#include "Playlist.h"

PlaylistPanCommand::PlaylistPanCommand(Playlist * snd, float _from, float _to, float t) : playlist(snd), from(_from), to(_to), time(t)
{
	// compute delta
	delta = (std::abs(from - to) * 10) / t;
}

void PlaylistPanCommand::execute()
{
	if (playlist)
	{
		if (!nearEqual(from, to))
		{
			lerpFinished = false;

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
		playlist->Pan(from);
	}
}

PlaylistPanCommand * PlaylistPanCommand::clone()
{
	return new PlaylistPanCommand(*this);
}
