#pragma once
#ifndef UPDATABLEREGCOMMAND_H
#define UPDATABLEREGCOMMAND_H

#include "Command.h"
class Updatable;

class UpdatableRegistrationCommand : public Command
{
public:
	UpdatableRegistrationCommand() = default;
	~UpdatableRegistrationCommand() {
		//DebugMsg::out("Update Registration Command Cleaned\n");
	};
	UpdatableRegistrationCommand(const UpdatableRegistrationCommand&) = default;
	UpdatableRegistrationCommand& operator=(const UpdatableRegistrationCommand&) = default;

	UpdatableRegistrationCommand(Updatable * _up);

	void execute() override;

private:

	Updatable* up;

};

#endif // !UPDATABLEREGCOMMAND_H
