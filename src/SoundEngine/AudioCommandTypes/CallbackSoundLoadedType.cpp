#include "CallbackSoundLoadedType.h"
#include "..\ThreadCallbackSoundLoadedCommand.h"

AudioThreadCommand * CallbackSoundLoadedType::visit()
{
	return new ThreadCallbackSoundLoadedCommand();
}
