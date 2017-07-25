#ifndef PLAYTYPE
#define PLAYTYPE

#include "AudioCommandType.h"
#include "AudioThreadCommand.h"

class ThreadPlayCommand;

class PlayType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static ThreadPlayCommand type;
};

#endif