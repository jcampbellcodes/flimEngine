#ifndef THREADSetEmitterOrientationCOMMAND
#define THREADSetEmitterOrientationCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetEmitterOrientationCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif