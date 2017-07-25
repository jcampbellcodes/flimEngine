#include "LoopType.h"
#include "..\ThreadLoopCommand.h"
AudioThreadCommand * LoopType::visit()
{
	return new ThreadLoopCommand();
}
