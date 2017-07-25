#include "CallbackSoundStartedType.h"
#include "..\ThreadCallbackSoundStartedCommand.h"
AudioThreadCommand * CallbackSoundStartedType::visit()
{
	return new ThreadCallbackSoundStartedCommand();
}
