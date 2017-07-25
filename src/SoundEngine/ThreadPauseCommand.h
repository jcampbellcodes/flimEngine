#ifndef THREADPauseCOMMAND
#define THREADPauseCOMMAND
#include "AudioThreadCommand.h"


class ThreadPauseCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif