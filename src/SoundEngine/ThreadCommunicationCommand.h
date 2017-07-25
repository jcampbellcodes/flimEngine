#pragma once
#ifndef THREADCOMMCOMMAND_H
#define THREADCOMMCOMMAND_H

#include "Command.h"
#include "Trace\Trace.h"
#include "SoundCallRegistry.h"

class ThreadCommunicationCommand : public Command
{
public:
	ThreadCommunicationCommand() = default;
	~ThreadCommunicationCommand()
	{
		//Trace::out("thread comm command deleted\n");
	}
	ThreadCommunicationCommand(const ThreadCommunicationCommand&) = default;
	ThreadCommunicationCommand& operator=(const ThreadCommunicationCommand&) = default;

	//virtual snd_err SetContext(SoundCallID , unsigned int ) { return snd_err::NOT_IN_USE; };
	virtual void execute() = 0;
private:
};


#endif