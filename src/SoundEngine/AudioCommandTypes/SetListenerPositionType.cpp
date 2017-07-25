#include "SetListenerPositionType.h"
#include "..\ThreadSetListenerPositionCommand.h"
AudioThreadCommand * SetListenerPositionType::visit()
{
	return new ThreadSetListenerPositionCommand();
}
