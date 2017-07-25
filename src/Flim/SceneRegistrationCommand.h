#pragma once
#ifndef SCENEREGISTRATIONCOMMAND_H
#define SCENEREGISTRATIONCOMMAND_H

#include "Command.h"

class SceneRegistrationCommand : public Command
{
public:
	SceneRegistrationCommand();
	~SceneRegistrationCommand();
	SceneRegistrationCommand(const SceneRegistrationCommand&);
	SceneRegistrationCommand& operator=(const SceneRegistrationCommand&);

	virtual void execute() override = 0;

private:

};

#endif 