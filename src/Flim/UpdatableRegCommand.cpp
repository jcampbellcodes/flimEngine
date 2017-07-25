#include "UpdatableRegCommand.h"

#include "Updatable.h"

UpdatableRegistrationCommand::UpdatableRegistrationCommand(Updatable * _up) : up(_up)
{
}

void UpdatableRegistrationCommand::execute()
{
	up->SceneRegistration();
}
