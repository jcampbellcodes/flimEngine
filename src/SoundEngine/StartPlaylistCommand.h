#pragma once
#ifndef StartPlaylistCommand_H
#define StartPlaylistCommand_H

#include "Command.h"
#include "Trace\Trace.h"
#include "SoundCallRegistry.h"
#include "snd_err.h"
#include "ThreadCommunicationCommand.h"

class StartPlaylistCommand : public ThreadCommunicationCommand
{
public:
	StartPlaylistCommand();
	StartPlaylistCommand(SoundCallID _id, unsigned int _handle, bool _3D);
	~StartPlaylistCommand()
	{
		//Trace::out("start playlist command deleted\n");
	}
	StartPlaylistCommand(const StartPlaylistCommand&) = default;
	StartPlaylistCommand& operator=(const StartPlaylistCommand&) = default;

	snd_err SetContext(SoundCallID _id, unsigned int _handle);
	virtual void execute() override;
private:
	unsigned int handle;
	SoundCallID id;
	bool is3D;

};


#endif