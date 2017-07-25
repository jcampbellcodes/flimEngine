#pragma once
#ifndef SoundExecutioner_H
#define SoundExecutioner_H

#include <list>
#include "Command.h"
#include "AzulCore.h"

class CallbackCommand;

class SoundExecutioner
{
public:
	SoundExecutioner() = default;
	~SoundExecutioner();
	SoundExecutioner(const SoundExecutioner&) = default;
	SoundExecutioner& operator=(const SoundExecutioner&) = default;

	void addCommand(CallbackCommand* in);
	//void addCommand(CallbackCommand* cmd);
	void ProcessInstantCommands();
	void ProcessDeferredCommands();

private:
	std::list<CallbackCommand*> instantDeploy;
	std::list<CallbackCommand*> deferredDeploy;


};

#endif