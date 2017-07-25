#include "TerminateSoundEngineType.h"
#include "..\ThreadTerminateSoundEngineCommand.h"


AudioThreadCommand * TerminateSoundEngineType::visit()
{
	return new ThreadTerminateSoundEngineCommand();
}

