#pragma once
#ifndef UPDATABLEDEREGCOMMAND_H
#define UPDATABLEREGCOMMAND_H

#include "Command.h"
class Updatable;

class UpdatableDeregistrationCommand : public Command
{
public:
	UpdatableDeregistrationCommand() = default;
	~UpdatableDeregistrationCommand() {
		//DebugMsg::out("Update Deregistration Command Cleaned\n");
	};
	UpdatableDeregistrationCommand(const UpdatableDeregistrationCommand&) = default;
	UpdatableDeregistrationCommand& operator=(const UpdatableDeregistrationCommand&) = default;

	UpdatableDeregistrationCommand(Updatable * _up);

	void execute() override;

private:

	Updatable* up;

};

#endif // !UPDATABLEREGCOMMAND_H