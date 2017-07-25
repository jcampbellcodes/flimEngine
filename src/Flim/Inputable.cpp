#include "Inputable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputableRegCommand.h"

#include "InputableDeregCommand.h"

errcode Inputable::SceneRegistration(AZUL_KEY key, input_type type)
{
	SceneManager::Register(this, key, type);
	regState = RegistrationState::REG;
	return errcode::success;
}

errcode Inputable::SceneDeregistration(AZUL_KEY key, input_type type)
{
	SceneManager::Deregister(this, key, type);
	regState = RegistrationState::DEREG;
	return errcode::success;
}

Inputable::Inputable()
{
	regState = RegistrationState::DEREG;
	// make the commands
	regCommand = nullptr;
	deregCommand = nullptr;

}

Inputable::~Inputable()
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
	//DebugMsg::out("Inputable cleaned\n");
}

errcode Inputable::SubmitInputRegistration(AZUL_KEY key, input_type type)
{
	SceneManager::GetCurrentScene().SubmitCommand(new InputableRegistrationCommand(this, key, type));
	regState = RegistrationState::REG_PENDING;
	return errcode::success;
}

errcode Inputable::SubmitInputDeregistration(AZUL_KEY key, input_type type)
{
	SceneManager::GetCurrentScene().SubmitCommand(new InputableDeregistrationCommand(this, key, type));
	regState = RegistrationState::DEREG_PENDING;
	return errcode::success;
}

std::list<Inputable*>::iterator Inputable::GetDeletionIterator()
{
	return deleteIter;
}

errcode Inputable::SetDeletionIterator(std::list<Inputable*>::iterator in)
{
	deleteIter = in;
	return errcode::success;
}
