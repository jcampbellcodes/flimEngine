#include "InitializeSoundType.h"
#include "..\ThreadInitializeSoundCommand.h"
AudioThreadCommand * InitializeSoundType::visit()
{
	return new ThreadInitializeSoundCommand();
}
