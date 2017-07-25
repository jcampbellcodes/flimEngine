#pragma once
#ifndef GameObjectREGCOMMAND_H
#define GameObjectREGCOMMAND_H

#include "Command.h"
class GameObject;

class GameObjectRegistrationCommand : public Command
{
public:
	GameObjectRegistrationCommand() = default;
	~GameObjectRegistrationCommand() {
		//DebugMsg::out("GO Registration Command Cleaned\n");
	};
	GameObjectRegistrationCommand(const GameObjectRegistrationCommand&) = default;
	GameObjectRegistrationCommand& operator=(const GameObjectRegistrationCommand&) = default;

	GameObjectRegistrationCommand(GameObject* go);

	void execute() override;

private:

	GameObject* go;

};

#endif // !GameObjectREGCOMMAND_H