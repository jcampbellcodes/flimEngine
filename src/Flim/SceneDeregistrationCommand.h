#pragma once
#ifndef SceneDeregistrationCommand_H

#define SceneDeregistrationCommand_H

#include "AzulCore.h"
#include "Command.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SceneDeregistrationCommand
///
/// \brief	A scene registration command.
///
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class SceneDeregistrationCommand : public Command
{
private:

public:
	SceneDeregistrationCommand()
	{

	};
	virtual ~SceneDeregistrationCommand() {
		//DebugMsg::out("Base SceneDeregistrationCommand Cleaned\n");
	};
	SceneDeregistrationCommand& operator=(const SceneDeregistrationCommand&) = default;
	SceneDeregistrationCommand(const SceneDeregistrationCommand&) = default;

	virtual void execute() override = 0;
};

#endif