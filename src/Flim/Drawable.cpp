#include "Drawable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "DrawableDeregCommand.h"
#include "DrawableRegCommand.h"

Drawable::Drawable()
{
	regState = RegistrationState::DEREG;
	// make the commands
	regCommand = new DrawableRegistrationCommand(this);
	deregCommand = new DrawableDeregistrationCommand(this);
}

Drawable::~Drawable()
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
	//DebugMsg::out("Drawable Cleaned\n");
}

errcode Drawable::SceneRegistration()
{
	assert(regState == RegistrationState::REG_PENDING);
	SceneManager::Register(this);
	regState = RegistrationState::REG;
	return errcode::success;
}

errcode Drawable::SceneDeregistration()
{
	assert(regState == RegistrationState::DEREG_PENDING);
	SceneManager::Deregister(this);
	regState = RegistrationState::DEREG;
	return errcode::success;
}

errcode Drawable::SubmitDrawRegistration()
{
	assert(regState == RegistrationState::DEREG);
	SceneManager::GetCurrentScene().SubmitCommand(regCommand);
	regState = RegistrationState::REG_PENDING;
	return errcode::success;
}

errcode Drawable::SubmitDrawDeregistration()
{
	assert(regState == RegistrationState::REG);
	SceneManager::GetCurrentScene().SubmitCommand(deregCommand);
	regState = RegistrationState::DEREG_PENDING;
	return errcode::success;
}

std::list<Drawable*>::iterator Drawable::GetDeletionIterator()
{
	return this->deleteIter;
}

errcode Drawable::SetDeletionIterator(std::list<Drawable*>::iterator in)
{
	this->deleteIter = in;
	return errcode::success;
}
