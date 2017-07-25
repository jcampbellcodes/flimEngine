#include "SetListenerOrientationType.h"
#include "..\ThreadSetListenerOrientationCommand.h"
AudioThreadCommand * SetListenerOrientationType::visit()
{
	return new ThreadSetListenerOrientationCommand();
}
