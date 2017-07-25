#include "PauseType.h"
#include "..\ThreadPauseCommand.h"
AudioThreadCommand * PauseType::visit()
{
	return new ThreadPauseCommand();
}
