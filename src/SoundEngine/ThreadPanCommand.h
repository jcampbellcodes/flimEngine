#ifndef THREADPanCOMMAND
#define THREADPanCOMMAND
#include "AudioThreadCommand.h"


class ThreadPanCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif