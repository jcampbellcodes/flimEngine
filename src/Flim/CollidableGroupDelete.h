#pragma once
// NON TEMPLATE BASE CLASS
#ifndef CollidableGroupDeleteCmdCommand_H

#define CollidableGroupDeleteCmdCommand_H

#include "AzulCore.h"
#include "Command.h"

class CollidableGroupDeleteCmd : public Command
{
private:

public:
	CollidableGroupDeleteCmd() = default;
	virtual ~CollidableGroupDeleteCmd() {
		//DebugMsg::out("Base CollidableGroupDeleteCmdCommand Cleaned\n");
	};
	CollidableGroupDeleteCmd& operator=(const CollidableGroupDeleteCmd&) = default;
	CollidableGroupDeleteCmd(const CollidableGroupDeleteCmd&) = default;

	virtual void execute() override {};
};

#endif