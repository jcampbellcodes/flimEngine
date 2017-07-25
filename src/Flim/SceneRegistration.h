#pragma once
#ifndef SceneRegistrationCommand_H

#define SceneRegistrationCommand_H

#include "AzulCore.h"
#include "Command.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SceneRegistrationCommand
///
/// \brief	A scene registration command.
///
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class SceneRegistrationCommand : public Command
{
private:

public:
	SceneRegistrationCommand()
	{

	};



	virtual ~SceneRegistrationCommand() {
		//DebugMsg::out("Base SceneRegistrationCommand Cleaned\n");
	};
	SceneRegistrationCommand& operator=(const SceneRegistrationCommand&) = default;
	SceneRegistrationCommand(const SceneRegistrationCommand&) = default;
	virtual void execute() override = 0;

};

#endif