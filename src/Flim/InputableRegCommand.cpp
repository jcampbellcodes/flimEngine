#include "InputableRegCommand.h"

#include "Inputable.h"

InputableRegistrationCommand::InputableRegistrationCommand(Inputable * _up, AZUL_KEY _key, input_type _type) : up(_up), key(_key), type(_type)
{
}

void InputableRegistrationCommand::execute()
{
	up->SceneRegistration(key, type);
}
