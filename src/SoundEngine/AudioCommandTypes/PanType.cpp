#include "PanType.h"
#include "..\ThreadPanCommand.h"

AudioThreadCommand * PanType::visit()
{
	return new ThreadPanCommand();
}
