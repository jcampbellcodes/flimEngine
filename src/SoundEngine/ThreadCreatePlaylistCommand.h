#ifndef THREADCreatePlaylistCOMMAND
#define THREADCreatePlaylistCOMMAND
#include "AudioThreadCommand.h"


class ThreadCreatePlaylistCommand : public AudioThreadCommand
{
public:
	void SetCommand(ThreadCommand& command) override { cmd = command; };

	void execute() override;

private:
	ThreadCommand cmd;
};

#endif