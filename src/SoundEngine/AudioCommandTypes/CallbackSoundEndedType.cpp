#include "CallbackSoundEndedType.h"
#include "..\ThreadCallbackSoundEndedCommand.h"

ThreadCallbackSoundEndedCommand CallbackSoundEndedType::type = ThreadCallbackSoundEndedCommand();

AudioThreadCommand * CallbackSoundEndedType::visit()
{
	return &CallbackSoundEndedType::type;
}
