#ifndef THREADCallbackSoundStartedCOMMAND
#define THREADCallbackSoundStartedCOMMAND
#include "AudioThreadCommand.h"


class ThreadCallbackSoundStartedCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif