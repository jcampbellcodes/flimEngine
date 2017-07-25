#include "SetReverbLevelType.h"
#include "..\ThreadSetReverbLevelCommand.h"
AudioThreadCommand * SetReverbLevelType::visit()
{
	return new ThreadSetReverbLevelCommand();
}
