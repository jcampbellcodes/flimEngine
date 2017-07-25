#pragma once
#ifndef HELLOCOMMAND_H

#define HELLOCOMMAND_H

#include "AzulCore.h"
#include "Command.h"
#include <map>

class HelloCommand : public Command
{
private:

public:
	HelloCommand() = default;
	~HelloCommand() {
		DebugMsg::out("Hello Command Cleaned\n");
	};
	HelloCommand& operator=(const HelloCommand&) = default;
	HelloCommand(const HelloCommand&) = default;

	void execute() override;
};

#endif