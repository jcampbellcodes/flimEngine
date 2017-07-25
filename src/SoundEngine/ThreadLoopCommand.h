#ifndef THREADLoopCOMMAND
#define THREADLoopCOMMAND
#include "AudioThreadCommand.h"


class ThreadLoopCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif