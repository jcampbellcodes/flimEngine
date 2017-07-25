#pragma once
#ifndef InputableDEREGCOMMAND_H
#define InputableREGCOMMAND_H

#include "Command.h"
#include "AzulCore.h"
#include "InputType.h"
class Inputable;

class InputableDeregistrationCommand : public Command
{
public:
	InputableDeregistrationCommand() = default;
	~InputableDeregistrationCommand() {
		//DebugMsg::out("Input Deregistration Command Cleaned\n");
	};
	InputableDeregistrationCommand(const InputableDeregistrationCommand&) = default;
	InputableDeregistrationCommand& operator=(const InputableDeregistrationCommand&) = default;

	InputableDeregistrationCommand(Inputable * _up, AZUL_KEY _key, input_type _type);

	void execute() override;

private:

	Inputable* up;
	AZUL_KEY key;
	input_type type;

};

#endif // !InputableREGCOMMAND_H