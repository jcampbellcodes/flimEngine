#ifndef THREADInitializeSoundCOMMAND
#define THREADInitializeSoundCOMMAND
#include "AudioThreadCommand.h"


class ThreadInitializeSoundCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif