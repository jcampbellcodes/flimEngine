#ifndef THREADSetReverbDensityCOMMAND
#define THREADSetReverbDensityCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetReverbDensityCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif