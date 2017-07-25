#ifndef THREADSetReverbSizeCOMMAND
#define THREADSetReverbSizeCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetReverbSizeCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif