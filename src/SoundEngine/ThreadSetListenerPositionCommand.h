#ifndef THREADSetListenerPositionCOMMAND
#define THREADSetListenerPositionCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetListenerPositionCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif