#ifndef THREADCallbackSoundEndedCOMMAND
#define THREADCallbackSoundEndedCOMMAND
#include "AudioThreadCommand.h"


class ThreadCallbackSoundEndedCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif