#include "GameobjDeregCommand.h"
#include "RegState.h"
#include "GameObject.h"

GameObjectDeregistrationCommand::GameObjectDeregistrationCommand(GameObject * _go) : go(_go)
{
}

void GameObjectDeregistrationCommand::execute()
{
	if(go->regStateGO == RegistrationState::DEREG_PENDING)
	{
		go->SceneExit();
	}
	go->regStateGO = RegistrationState::DEREG;
}
