#pragma once
#ifndef HANDLEMANAGER_H
#define HANDLEMANAGER_H

#define HANDLE_TABLE_SIZE 16000
#define INVALID_HANDLE 0x0
#define INITIAL_HANDLE 0xAAAA0000


#include "snd_err.h"


/*

TODO

Change vector to array
methods -- 

Create() generates the ID and adds to the collection

Check() check position in array and determines if resource can be used 

Destroy() tells the manager to invalidate the position in the collection



-- inside handle constructor, call Create()
-- inside sound, call Check()
-- in sound destructor, call Destroy()

*/


class SoundTest;
class ISound;
class SoundErr;
class Handle;

struct Lock
{
	unsigned int ID;
};

class HandleManager
{
	// singleton
private:
	HandleManager();
	HandleManager(const HandleManager&) = delete;
	HandleManager& operator=(const HandleManager&) = delete;
	~HandleManager();

	static HandleManager* instance;
	static HandleManager& Instance()
	{
		if (!instance)
		{
			instance = new HandleManager();
		}
		return *instance;
	}

	// put a collection here. a linked list? maybe STL map for simplicity. hashing involved?
	Lock gatekeeper[HANDLE_TABLE_SIZE];
	unsigned int lastFreeNode;


	// put mechanism for hashing unique IDs here
	unsigned int curID;



	// internal methods
	unsigned int GetUniqueID();

	bool findNextFree(unsigned int& index);

	snd_err privCheckID(unsigned int& ID, unsigned int& location);
	snd_err privCheckID(Handle& handle);
	snd_err privRegisterHandle(unsigned int& ID, unsigned int& location);
	snd_err privDeregisterHandle(unsigned int& ID, unsigned int& location);


public:

	// also ask the manager to create/remove the sound calls for you
	static snd_err RegisterHandle(unsigned int& ID, unsigned int& location)
	{
		return Instance().privRegisterHandle(ID, location);
	}

	static snd_err CheckID(unsigned int& ID, unsigned int& location)
	{
		return Instance().privCheckID(ID, location);
	}

	static snd_err CheckID(Handle& handle)
	{
		return Instance().privCheckID(handle);
	}

	static snd_err DeregisterHandle(unsigned int& ID, unsigned int& location)
	{
		return Instance().privDeregisterHandle(ID, location);
	}
};

#endif