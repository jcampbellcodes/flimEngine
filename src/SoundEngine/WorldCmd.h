#pragma once
#ifndef WorldCOMMAND_H

#define WorldCOMMAND_H

#include "AzulCore.h"
#include "Command.h"

#include <map>

class WorldCommand : public Command
{
private:

public:
	WorldCommand() = default;
	~WorldCommand() {
		DebugMsg::out("World Command Cleaned\n");
	};
	WorldCommand& operator=(const WorldCommand&) = default;
	WorldCommand(const WorldCommand&) = default;

	void execute() override;

};

#endif