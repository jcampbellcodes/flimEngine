#ifndef THREADDeactivateFilterCOMMAND
#define THREADDeactivateFilterCOMMAND
#include "AudioThreadCommand.h"


class ThreadDeactivateFilterCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif