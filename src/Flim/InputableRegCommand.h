#pragma once
#ifndef InputableREGCOMMAND_H
#define InputableREGCOMMAND_H

#include "Command.h"
#include "AzulCore.h"
#include "InputType.h"
class Inputable;

class InputableRegistrationCommand : public Command
{
public:
	InputableRegistrationCommand() = default;
	~InputableRegistrationCommand() {
		//DebugMsg::out("Input Registration Command Cleaned\n");
	};
	InputableRegistrationCommand(const InputableRegistrationCommand&) = default;
	InputableRegistrationCommand& operator=(const InputableRegistrationCommand&) = default;

	InputableRegistrationCommand(Inputable * _up, AZUL_KEY _key, input_type _type);

	void execute() override;

private:

	Inputable* up;
	AZUL_KEY key;
	input_type type;

};

#endif // !InputableREGCOMMAND_H
