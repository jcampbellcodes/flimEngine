#include "SetReverbPredelay.h"
#include "..\ThreadSetReverbPredelayCommand.h"
AudioThreadCommand * SetReverbPredelayType::visit()
{
	return new ThreadSetReverbPredelayCommand();
}
