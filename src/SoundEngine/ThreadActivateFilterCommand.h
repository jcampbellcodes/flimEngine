#ifndef THREADActivateFilterCOMMAND
#define THREADActivateFilterCOMMAND
#include "AudioThreadCommand.h"


class ThreadActivateFilterCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif