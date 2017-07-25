#include "SetEmitterOrientationType.h"
#include "..\ThreadSetEmitterOrientationCommand.h"
AudioThreadCommand * SetEmitterOrientationType::visit()
{
	return new ThreadSetEmitterOrientationCommand();
}
