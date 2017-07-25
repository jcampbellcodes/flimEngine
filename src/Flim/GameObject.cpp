#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

GameObject::GameObject()
{
	regStateGO = RegistrationState::DEREG;

	regCommand = new GameObjectRegistrationCommand(this);
	deregCommand = new GameObjectDeregistrationCommand(this);
}

GameObject::~GameObject()
{
	if (regCommand)
	{
		delete regCommand;
		regCommand = nullptr;
	}
	if (deregCommand)
	{
		delete deregCommand;
		deregCommand = nullptr;
	}
}

errcode GameObject::SubmitEntry()
{
	errcode err = errcode::success;
	//assert(regStateGO == RegistrationState::DEREG);
	if (regStateGO == RegistrationState::DEREG)
	{
		SceneManager::GetCurrentScene().SubmitCommand(regCommand);
		regStateGO = RegistrationState::REG_PENDING;
		err =  errcode::success;
	}
	else
	{
		err = errcode::failure;
	}
	return err;
}

errcode GameObject::SubmitExit()
{
	errcode err = errcode::success;
	//assert(regStateGO == RegistrationState::REG);
	if (regStateGO == RegistrationState::REG)
	{
		SceneManager::GetCurrentScene().SubmitCommand(deregCommand);
		regStateGO = RegistrationState::DEREG_PENDING;
		err = errcode::success;
	}
	else
	{
		err = errcode::failure;
	}
	return err;
}