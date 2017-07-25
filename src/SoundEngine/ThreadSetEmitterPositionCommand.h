#ifndef THREADSetEmitterPositionCOMMAND
#define THREADSetEmitterPositionCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetEmitterPositionCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif