#pragma once
#ifndef GameObjectDEREGCOMMAND_H
#define GameObjectDEREGCOMMAND_H

#include "Command.h"
class GameObject;

class GameObjectDeregistrationCommand : public Command
{
public:
	GameObjectDeregistrationCommand() = delete;
	~GameObjectDeregistrationCommand() {
		//DebugMsg::out("GO Deregistration Command Cleaned\n");
	};
	GameObjectDeregistrationCommand(const GameObjectDeregistrationCommand&) = default;
	GameObjectDeregistrationCommand& operator=(const GameObjectDeregistrationCommand&) = default;

	GameObjectDeregistrationCommand(GameObject* go);

	void execute() override;

private:

	GameObject* go;

};

#endif // !GameObjectREGCOMMAND_H