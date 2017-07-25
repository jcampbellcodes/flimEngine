#include "DeactivateFilterType.h"
#include "..\ThreadDeactivateFilterCommand.h"
AudioThreadCommand * DeactivateFilterType::visit()
{
	return new ThreadDeactivateFilterCommand();
}
