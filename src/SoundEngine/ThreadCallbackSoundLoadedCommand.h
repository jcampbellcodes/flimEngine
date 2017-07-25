#ifndef THREADThreadCallbackSoundLoadedCOMMAND
#define THREADThreadCallbackSoundLoadedCOMMAND
#include "AudioThreadCommand.h"


class ThreadCallbackSoundLoadedCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif