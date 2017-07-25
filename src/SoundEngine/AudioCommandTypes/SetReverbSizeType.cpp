#include "SetReverbSizeType.h"
#include "..\ThreadSetReverbSizeCommand.h"
AudioThreadCommand * SetReverbSizeType::visit()
{
	return new ThreadSetReverbSizeCommand();
}
