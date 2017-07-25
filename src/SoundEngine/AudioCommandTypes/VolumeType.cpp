#include "VolumeType.h"

#include "..\ThreadVolumeCommand.h"

AudioThreadCommand * VolumeType::visit()
{
	return new ThreadVolumeCommand();
}
