#include "GameobjRegCommand.h"
#include "RegState.h"
#include "GameObject.h"

GameObjectRegistrationCommand::GameObjectRegistrationCommand(GameObject * _go) : go(_go)
{
}

void GameObjectRegistrationCommand::execute()
{
	assert(go->regStateGO == RegistrationState::REG_PENDING);
	go->SceneEntry();
	go->regStateGO = RegistrationState::REG;
}
