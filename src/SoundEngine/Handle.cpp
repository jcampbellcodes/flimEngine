#include "Handle.h"
#include "HandleManager.h"
#include "AzulCore.h"

Handle::Handle()
{
	// -- tell handle manager to create
	HandleManager::RegisterHandle(this->ID, this->index);

	//DebugMsg::out("made a handle at ID %x and index %d\n", ID, index);
}

Handle::~Handle()
{
	// -- tell handle manager to destroy
	HandleManager::DeregisterHandle(this->ID, this->index);

	//DebugMsg::out("destroyed a handle at ID %x and index %d\n", ID, index);
}

unsigned int& Handle::GetID()
{
	return ID;
}

unsigned int& Handle::GetIndex()
{
	return index;
}
