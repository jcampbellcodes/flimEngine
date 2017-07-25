#include "IndividualSoundEnded.h"
#include "Playlist.h"

IndividualSoundEnded::IndividualSoundEnded(Playlist * p) : playlist(p)
{
	this->commandType = CMDTYPES::STREAM_END;
}

void IndividualSoundEnded::execute()
{
	// this is called from the longest sound
	playlist->SoundEnded();
}

IndividualSoundEnded * IndividualSoundEnded::clone()
{
	return new IndividualSoundEnded(*this);
}
