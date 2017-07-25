#include "SetEmitterPositionType.h"
#include "..\ThreadSetEmitterPositionCommand.h"
AudioThreadCommand * SetEmitterPositionType::visit()
{
	return new ThreadSetEmitterPositionCommand();
}
