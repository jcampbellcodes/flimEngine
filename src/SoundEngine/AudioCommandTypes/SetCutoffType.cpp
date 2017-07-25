#include "SetCutoffType.h"
#include "..\ThreadSetCutoffCommand.h"
AudioThreadCommand * SetCutoffType::visit()
{
	return new ThreadSetCutoffCommand();
}
