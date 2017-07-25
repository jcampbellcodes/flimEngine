#include "SetReverbPresetType.h"
#include "..\ThreadSetReverbPresetCommand.h"
AudioThreadCommand * SetReverbPresetType::visit()
{
	return new ThreadSetReverbPresetCommand();
}
