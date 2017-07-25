#include "LoadWaveType.h"
#include "..\ThreadLoadWaveCommand.h"
AudioThreadCommand * LoadWaveType::visit()
{
	return new ThreadLoadWaveCommand();
}