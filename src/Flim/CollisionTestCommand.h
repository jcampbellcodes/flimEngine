#pragma once
#ifndef CollisionTestCommand_H

#define CollisionTestCommand_H

#include "AzulCore.h"
#include "Command.h"

class CollisionTestCommand : public Command
{
private:

public:
	CollisionTestCommand() = default;
	virtual ~CollisionTestCommand() {
		//DebugMsg::out("Base CollisionTestCommand Cleaned\n");
	};
	CollisionTestCommand& operator=(const CollisionTestCommand&) = default;
	CollisionTestCommand(const CollisionTestCommand&) = default;

	virtual void execute() override{};
};

#endif