#include "Updatable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "UpdatableRegCommand.h"

#include "UpdatableDeregCommand.h"

errcode Updatable::SceneRegistration()
{
	assert(regState == RegistrationState::REG_PENDING);
	SceneManager::Register(this);
	regState = RegistrationState::REG;
	return errcode::success;
}

errcode Updatable::SceneDeregistration()
{
	assert(regState == RegistrationState::DEREG_PENDING);
	SceneManager::Deregister(this);
	regState = RegistrationState::DEREG;
	return errcode::success;
}

Updatable::Updatable()
{
	regState = RegistrationState::DEREG;
	// make the commands
	regCommand = new UpdatableRegistrationCommand(this);
	deregCommand = new UpdatableDeregistrationCommand(this);
}

Updatable::~Updatable()
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
	//DebugMsg::out("Updatable cleaned\n");
}

errcode Updatable::SubmitUpdateRegistration()
{
	assert(regState == RegistrationState::DEREG);
	SceneManager::GetCurrentScene().SubmitCommand(regCommand);
	regState = RegistrationState::REG_PENDING;
	return errcode::success;
}

errcode Updatable::SubmitUpdateDeregistration()
{
	assert(regState == RegistrationState::REG);
	SceneManager::GetCurrentScene().SubmitCommand(deregCommand);
	regState = RegistrationState::DEREG_PENDING;
	return errcode::success;
}
