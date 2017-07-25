#include "InternalSoundEnded.h"
#include "Playlist.h"

InternalSoundEnded::InternalSoundEnded(Playlist * p) : playlist(p)
{
	this->commandType = CMDTYPES::STREAM_END;
}

void InternalSoundEnded::execute()
{
	// this is called from the longest sound
	playlist->SendCallbackSoundEnded();
}

InternalSoundEnded * InternalSoundEnded::clone()
{
	return new InternalSoundEnded(*this);
}
