#include "AudioCommandFactory.h"
#include "AudioCommandType.h"
#include "AudioThreadCommand.h"
AudioThreadCommand * AudioCommandFactory::Create(AudioCommandType * obj)
{
	return obj->visit();
};