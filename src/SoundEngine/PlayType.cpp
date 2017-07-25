#include "PlayType.h"
#include "ThreadPlayCommand.h"
ThreadPlayCommand PlayType::type = ThreadPlayCommand();
AudioThreadCommand * PlayType::visit()
{
	//return new ThreadPlayCommand();
	return &PlayType::type;
}
