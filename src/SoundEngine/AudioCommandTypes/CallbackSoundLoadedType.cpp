#include "CallbackSoundLoadedType.h"
#include "..\ThreadCallbackSoundLoadedCommand.h"
ThreadCallbackSoundLoadedCommand CallbackSoundLoadedType::type = ThreadCallbackSoundLoadedCommand();
AudioThreadCommand * CallbackSoundLoadedType::visit()
{
	return &CallbackSoundLoadedType::type;
}
