#include "UpdatableDeregCommand.h"

#include "Updatable.h"

UpdatableDeregistrationCommand::UpdatableDeregistrationCommand(Updatable * _up) : up(_up)
{
}

void UpdatableDeregistrationCommand::execute()
{
	up->SceneDeregistration();
}
