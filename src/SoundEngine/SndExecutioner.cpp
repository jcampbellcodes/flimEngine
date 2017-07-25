#include "SndExecutioner.h"
#include "Command.h"
#include "CallbackCommand.h"
#include "SoundManager.h"
#include "CallbackManager.h"

void SoundExecutioner::addCommand(CallbackCommand * in)
{
	if (in->instant_execute)
	{
		instantDeploy.push_back(in);
	}
	else
	{
		deferredDeploy.push_back(in);
	}
}

SoundExecutioner::~SoundExecutioner()
{
	
	//DebugMsg::out("SoundExecutioner Cleaned\n");

	std::list<CallbackCommand*>::iterator iter = deferredDeploy.begin();

	while (iter != deferredDeploy.end()) // maybe here check how many times the command should fire? not internally. then decide whether to insert again or to remove
	{
		delete (*iter);
		(*iter) = nullptr;
		iter++;
	}
	deferredDeploy.clear();

	std::list<CallbackCommand*>::iterator iter1 = instantDeploy.begin();

	while (iter1 != instantDeploy.end())
	{
		delete (*iter1);
		(*iter1) = nullptr;
		iter1++;
	}
	instantDeploy.clear();
	
}

void SoundExecutioner::ProcessInstantCommands()
{
	std::list<CallbackCommand*>::iterator iter = instantDeploy.begin();

	while (iter != instantDeploy.end())
	{
		(*iter)->execute();
		delete(*iter);
		iter++;
	}
	instantDeploy.clear();
}

// add process defer commands -- on deferred list, add to timer at time 0

void SoundExecutioner::ProcessDeferredCommands()
{
	std::list<CallbackCommand*>::iterator iter = deferredDeploy.begin();

	while (iter != deferredDeploy.end()) // maybe here check how many times the command should fire? not internally. then decide whether to insert again or to remove
	{
		SoundManager::InsertTimelineCommand((*iter));
		iter++;
	}
	deferredDeploy.clear();
}
