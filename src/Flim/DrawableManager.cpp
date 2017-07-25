#include "DrawableManager.h"
#include "Drawable.h"

#include "AzulCore.h"

errcode DrawableManager::ProcessElements()
{
	// iterate through list and call update on Drawables
	std::list<Drawable*>::const_iterator iter = storageList.begin();

	while (iter != storageList.end())
	{
		// check errcode of updates?
		(*iter)->Draw();
		iter++;
	}

	// draw 2D AFTER all the rest
	iter = storageList.begin();

	while (iter != storageList.end())
	{
		// check errcode of updates?
		(*iter)->Draw2D();
		iter++;
	}

	return errcode::success;

}

errcode DrawableManager::Register(Drawable * in)
{
	// add in tothe list to be updated
	in->SetDeletionIterator(storageList.insert(storageList.end(), in));

	return errcode::success;
}

errcode DrawableManager::Deregister(Drawable * in)
{
	// remove in from the list to be updated
	storageList.erase(in->GetDeletionIterator());

	// get an iterator -- use erase
	return errcode::success;
}
