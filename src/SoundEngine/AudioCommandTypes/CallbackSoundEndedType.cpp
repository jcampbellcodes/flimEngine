#include "CallbackSoundEndedType.h"
#include "..\ThreadCallbackSoundEndedCommand.h"
AudioThreadCommand * CallbackSoundEndedType::visit()
{
	return new ThreadCallbackSoundEndedCommand();
}
