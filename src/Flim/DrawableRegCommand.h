#pragma once
#ifndef DRAWABLEREGCOMMAND_H
#define DRAWABLEREGCOMMAND_H

#include "Command.h"
class Drawable;

class DrawableRegistrationCommand : public Command
{
public:
	DrawableRegistrationCommand() = default;
	~DrawableRegistrationCommand() {
		//DebugMsg::out("Draw Registration Command Cleaned\n");
	};
	DrawableRegistrationCommand(const DrawableRegistrationCommand&) = default;
	DrawableRegistrationCommand& operator=(const DrawableRegistrationCommand&) = default;

	DrawableRegistrationCommand(Drawable* draw);

	void execute() override;

private:

	Drawable* draw;

};

#endif // !DrawableREGCOMMAND_H