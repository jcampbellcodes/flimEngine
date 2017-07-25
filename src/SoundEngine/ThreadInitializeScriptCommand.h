#ifndef THREADInitializeScriptCOMMAND
#define THREADInitializeScriptCOMMAND
#include "AudioThreadCommand.h"


class ThreadInitializeScriptCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif