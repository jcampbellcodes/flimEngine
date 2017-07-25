#include "UpdatableManager.h"
#include "Updatable.h"

#include "AzulCore.h"

errcode UpdatableManager::ProcessElements()
{
	// iterate through list and call update on updatables
	std::list<Updatable*>::const_iterator iter = storageList.begin();

	while (iter != storageList.end())
	{
		// check errcode of updates?
		(*iter)->Update();
		iter++;
	}

	return errcode::success;

}

errcode UpdatableManager::Register(Updatable * in)
{
	// add in tothe list to be updated
	in->deleteIter = storageList.insert(storageList.end(), in);

	return errcode::success;
}

errcode UpdatableManager::Deregister(Updatable * in)
{
	// remove in from the list to be updated
	storageList.erase(in->deleteIter);

	// get an iterator -- use erase
	return errcode::success;
}
