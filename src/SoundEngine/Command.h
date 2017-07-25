#pragma once
#ifndef COMMAND_H

#define COMMAND_H

#include "AzulCore.h"
#include <map>

class Command
{
private:

public:
	Command() = default;
	~Command() {
		//DebugMsg::out("Base Command Cleaned\n");
	};
	Command& operator=(const Command&) = default;
	Command(const Command&) = default;

	virtual void execute() = 0;


};

#endif