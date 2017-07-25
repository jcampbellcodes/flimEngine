#pragma once
#ifndef DrawableDEREGCOMMAND_H
#define DrawableREGCOMMAND_H

#include "Command.h"
class Drawable;

class DrawableDeregistrationCommand : public Command
{
public:
	DrawableDeregistrationCommand() = delete;
	~DrawableDeregistrationCommand() {
		//DebugMsg::out("Draw Deregistration Command Cleaned\n");
	};
	DrawableDeregistrationCommand(const DrawableDeregistrationCommand&) = default;
	DrawableDeregistrationCommand& operator=(const DrawableDeregistrationCommand&) = default;

	DrawableDeregistrationCommand(Drawable* draw);

	void execute() override;

private:

	Drawable* draw;

};

#endif // !DrawableREGCOMMAND_H