#include "InitializeScriptType.h"
#include "..\ThreadInitializeScriptCommand.h"
AudioThreadCommand * InitializeScriptType::visit()
{
	return new ThreadInitializeScriptCommand();
}
