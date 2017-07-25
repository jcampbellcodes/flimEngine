#ifndef THREADSetReverbTimeCOMMAND
#define THREADSetReverbTimeCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetReverbTimeCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif