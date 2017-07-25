#pragma once
#ifndef CallbackCommand_H

#define CallbackCommand_H

#include "AzulCore.h"
#include <map>
#include "CallbackManager.h"
#include "AudioCommand.h"


class CallbackCommand : public AudioCommand
{
protected:
	friend class CallbackMailbox;
	friend class SoundExecutioner;
	// parameters
	bool instant_execute; // if you set this to true, be aware your command will fire in a blocking call. Risky!
	CMDTYPES commandType = CMDTYPES::NO_TYPE;

	Sound* secondarySound;

public:
	CallbackCommand();
	virtual ~CallbackCommand() {
		//DebugMsg::out("Base CallbackCommand Cleaned\n");
	};
	CallbackCommand& operator=(const CallbackCommand&) = default;
	CallbackCommand(const CallbackCommand&) = default;

	virtual void execute() = 0;
	virtual snd_err AttachSecondarySound(Sound* sound);

	virtual CallbackCommand* clone() override = 0;

	std::multimap<int, CallbackCommand*>::const_iterator deleteIter;
};

#endif