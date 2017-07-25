#ifndef THREADTerminateSoundEngineCOMMAND
#define THREADTerminateSoundEngineCOMMAND
#include "AudioThreadCommand.h"


class ThreadTerminateSoundEngineCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif