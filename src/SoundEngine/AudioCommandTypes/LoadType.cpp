#include "LoadType.h"
#include "..\ThreadLoadCommand.h"
AudioThreadCommand * LoadType::visit()
{
	return new ThreadLoadCommand();
}
