#ifndef THREADTerminateFileThreadCOMMAND
#define THREADTerminateFileThreadCOMMAND
#include "AudioThreadCommand.h"


class ThreadTerminateFileThreadCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif