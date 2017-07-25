#include "HandleManager.h"
#include "Handle.h"
#include "Sound.h"

#include "snd_err.h"

HandleManager* HandleManager::instance = nullptr;

const unsigned int invalidHandle = INVALID_HANDLE;
const unsigned int startID = INITIAL_HANDLE;

HandleManager::HandleManager() : curID(startID), lastFreeNode(0)
{
	unsigned int i = 0;
	while (i < HANDLE_TABLE_SIZE)
	{
		this->gatekeeper[i].ID = invalidHandle;
		i++;
	}
}

HandleManager::~HandleManager()
{
	this->curID = startID;

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
	//DebugMsg::out("HandleManager cleaned");
}

unsigned int HandleManager::GetUniqueID()
{
	this->curID++;
	return curID;
}

bool HandleManager::findNextFree(unsigned int & index)
{
	bool status = false;
	unsigned int i = this->lastFreeNode;
	while (i < HANDLE_TABLE_SIZE)
	{
		if (gatekeeper[i].ID == invalidHandle)
		{
			lastFreeNode = i;
			index = i;
			status = true;

			break;
		}
		i++;
	}

	return status;
}


snd_err HandleManager::privCheckID(unsigned int& ID, unsigned int& location)
{
	snd_err err;
	Lock lock = this->gatekeeper[location];

	if (ID == lock.ID)
	{
		err = snd_err::OK;
	}
	else
	{
		err = snd_err::BAD_HANDLE;
	}

	return err;
}

snd_err HandleManager::privCheckID(Handle & handle)
{
	snd_err err;
	Lock lock = this->gatekeeper[handle.GetIndex()];

	if (handle.GetID() == lock.ID)
	{
		err = snd_err::OK;
	}
	else
	{
		err = snd_err::BAD_HANDLE;
	}

	return err;
}

snd_err HandleManager::privRegisterHandle(unsigned int& ID, unsigned int& location)
{
	snd_err err;

	// find next open space -- if it exists, put it there. else return error
	if (findNextFree(location))
	{
		// generate the ID
		unsigned int newID = GetUniqueID();

		ID = newID;
		gatekeeper[location].ID = newID;
		err = snd_err::OK;
	}
	else
	{
		// all full...... somehow
		err = snd_err::ERR;
	}

	return err;
}

snd_err HandleManager::privDeregisterHandle(unsigned int& ID, unsigned int& location)
{
	// just telling the gatekeeper you are now free
	snd_err err = snd_err::ERR;

	err = HandleManager::CheckID(ID, location);
	//assert(err == snd_err::OK);

	gatekeeper[location].ID = invalidHandle;

	return snd_err::OK;
}
