#pragma once
#ifndef TerminateSoundEngineCommand_H
#define TerminateSoundEngineCommand_H

#include "Command.h"
#include "Trace\Trace.h"
#include "SoundCallRegistry.h"
#include "snd_err.h"
#include "ThreadCommunicationCommand.h"

class TerminateSoundEngineCommand : public ThreadCommunicationCommand
{
public:
	TerminateSoundEngineCommand() = default;
	~TerminateSoundEngineCommand()
	{
		//Trace::out("start playlist command deleted\n");
	}
	TerminateSoundEngineCommand(const TerminateSoundEngineCommand&) = default;
	TerminateSoundEngineCommand& operator=(const TerminateSoundEngineCommand&) = default;
	virtual void execute() override;
private:

};


#endif