#ifndef THREADSetReverbPredelayCOMMAND
#define THREADSetReverbPredelayCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetReverbPredelayCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif