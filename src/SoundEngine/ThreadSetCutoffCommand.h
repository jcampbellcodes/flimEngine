#ifndef THREADSetCutoffCOMMAND
#define THREADSetCutoffCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetCutoffCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif