#pragma once
// NON TEMPLATE BASE CLASS
#ifndef CollisionUpdateCommandCommand_H

#define CollisionUpdateCommandCommand_H

#include "AzulCore.h"
#include "Command.h"

class CollisionUpdateCommand : public Command
{
private:

public:
	CollisionUpdateCommand() = default;
	virtual ~CollisionUpdateCommand() {
		//DebugMsg::out("Base CollisionUpdateCommandCommand Cleaned\n");
	};
	CollisionUpdateCommand& operator=(const CollisionUpdateCommand&) = default;
	CollisionUpdateCommand(const CollisionUpdateCommand&) = default;

	virtual void execute() override {};
};

#endif