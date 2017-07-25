#include "SetReverbDensityType.h"
#include "..\ThreadSetReverbDensityCommand.h"
AudioThreadCommand * SetReverbDensityType::visit()
{
	return new ThreadSetReverbDensityCommand();
}
