#ifndef THREADLoadCOMMAND
#define THREADLoadCOMMAND
#include "AudioThreadCommand.h"


class ThreadLoadCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif