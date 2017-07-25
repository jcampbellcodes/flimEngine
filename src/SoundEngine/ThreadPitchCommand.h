#ifndef THREADPitchCOMMAND
#define THREADPitchCOMMAND
#include "AudioThreadCommand.h"


class ThreadPitchCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif