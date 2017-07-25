#include "StopType.h"
#include "..\ThreadStopCommand.h"
AudioThreadCommand * StopType::visit()
{
	return new ThreadStopCommand();
}
