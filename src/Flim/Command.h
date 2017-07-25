#pragma once
#ifndef COMMAND_H

#define COMMAND_H

#include "AzulCore.h"

class Command
{
private:

public:
	Command()
	{
		//DebugMsg::out("base command");
	}

	virtual void execute() {};

	virtual ~Command() {
		//DebugMsg::out("Base Command Cleaned\n");
	};
	Command& operator=(const Command&) = default;
	Command(const Command&) = default;


};

#endif