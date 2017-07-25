#include "InputableDeregCommand.h"

#include "Inputable.h"

InputableDeregistrationCommand::InputableDeregistrationCommand(Inputable * _up, AZUL_KEY _key, input_type _type) : up(_up), key(_key), type(_type)
{
}

void InputableDeregistrationCommand::execute()
{
	up->SceneRegistration(key, type);
}
