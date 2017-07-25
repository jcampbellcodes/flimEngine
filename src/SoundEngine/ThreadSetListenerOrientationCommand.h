#ifndef THREADSetListenerOrientationCOMMAND
#define THREADSetListenerOrientationCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetListenerOrientationCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif