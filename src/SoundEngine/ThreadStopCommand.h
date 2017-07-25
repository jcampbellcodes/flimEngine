#ifndef THREADStopCOMMAND
#define THREADStopCOMMAND
#include "AudioThreadCommand.h"


class ThreadStopCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif