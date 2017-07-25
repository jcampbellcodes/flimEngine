#pragma once
#ifndef CallbackSoundEndedCOMMAND_H
#define CallbackSoundEndedCOMMAND_H

#include "Command.h"
#include "Trace\Trace.h"
#include "SoundCallRegistry.h"
#include "snd_err.h"
#include "ThreadCommunicationCommand.h"

class CallbackSoundEndedCommand : public ThreadCommunicationCommand
{
public:
	CallbackSoundEndedCommand();
	CallbackSoundEndedCommand(SoundCallID _id, unsigned int _handle);
	~CallbackSoundEndedCommand()
	{
		//Trace::out("callback sound command deleted\n");
	}
	CallbackSoundEndedCommand(const CallbackSoundEndedCommand&) = default;
	CallbackSoundEndedCommand& operator=(const CallbackSoundEndedCommand&) = default;

	snd_err SetContext(SoundCallID _id, unsigned int _handle);
	virtual void execute() override;
private:
	unsigned int handle;
	SoundCallID id;

};


#endif