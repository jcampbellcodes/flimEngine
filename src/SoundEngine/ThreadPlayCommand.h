#ifndef THREADPLAYCOMMAND
#define THREADPLAYCOMMAND
#include "AudioThreadCommand.h"


class ThreadPlayCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif