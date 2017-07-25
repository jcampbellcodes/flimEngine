#include "CallbackCommand.h"

CallbackCommand::CallbackCommand()
{
	// parameters
	instant_execute = false; // if you set this to true, be aware your command will fire in a blocking call. Risky!
	secondarySound = nullptr;
}
snd_err CallbackCommand::AttachSecondarySound(Sound * _sound)
{
	snd_err err = snd_err::OK;

	if (_sound)
	{
		this->secondarySound = _sound;
	}
	else
	{
		err = snd_err::NULLPTR;
	}

	return err;
}
;
