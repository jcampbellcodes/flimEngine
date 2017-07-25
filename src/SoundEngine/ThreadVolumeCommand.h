#ifndef THREADVolumeCOMMAND
#define THREADVolumeCOMMAND
#include "AudioThreadCommand.h"


class ThreadVolumeCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif