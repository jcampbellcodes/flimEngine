#include "SetReverbTimeType.h"
#include "..\ThreadSetReverbTimeCommand.h"
AudioThreadCommand * SetReverbTimeType::visit()
{
	return new ThreadSetReverbTimeCommand();
}
