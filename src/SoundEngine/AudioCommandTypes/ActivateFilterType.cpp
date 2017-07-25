#include "ActivateFilterType.h"
#include "..\ThreadActivateFilterCommand.h"
AudioThreadCommand * ActivateFilterType::visit()
{
	return new ThreadActivateFilterCommand();
}
