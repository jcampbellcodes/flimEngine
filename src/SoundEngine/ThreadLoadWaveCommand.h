#ifndef THREADLoadWaveCOMMAND
#define THREADLoadWaveCOMMAND
#include "AudioThreadCommand.h"


class ThreadLoadWaveCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif