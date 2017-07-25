#include "ActivateFilterType.h"
#include "..\ThreadActivateFilterCommand.h"
ThreadActivateFilterCommand ActivateFilterType::type = ThreadActivateFilterCommand();

AudioThreadCommand * ActivateFilterType::visit()
{
	return &ActivateFilterType::type;
}
