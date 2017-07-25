#include "PitchType.h"
#include "..\ThreadPitchCommand.h"
AudioThreadCommand * PitchType::visit()
{
	return new ThreadPitchCommand();
}
