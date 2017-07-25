#pragma once
#ifndef AssignCallbackCOMMAND_H

#define AssignCallbackCOMMAND_H

#include "AzulCore.h"
#include "AudioCommand.h"

#include <map>
#include "Sound.h"
#include "CallbackCommand.h"

class AssignCallbackCommand : public AudioCommand
{
private:
	CallbackCommand* cmd;


public:
	AssignCallbackCommand() = delete;
	AssignCallbackCommand(CallbackCommand* _cmd, Sound* _snd);
	AssignCallbackCommand(CallbackCommand* _cmd);
	~AssignCallbackCommand() {
		//DebugMsg::out("Assign Callback Command Cleaned\n");
	};
	AssignCallbackCommand& operator=(const AssignCallbackCommand&) = default;
	AssignCallbackCommand(const AssignCallbackCommand&) = default;

	void execute() override;

	AssignCallbackCommand* clone() override;

};

#endif