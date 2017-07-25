#ifndef THREADSetReverbPresetCOMMAND
#define THREADSetReverbPresetCOMMAND
#include "AudioThreadCommand.h"


class ThreadSetReverbPresetCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif