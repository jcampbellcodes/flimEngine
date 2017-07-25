#ifndef THREADSetReverbLevelCOMMAND
#define THREADSetReverbLevelCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetReverbLevelCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif