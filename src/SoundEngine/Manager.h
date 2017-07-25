#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "snd_err.h"
#include "List.h"

// An abstract class to create resource managers easily

// methods -- Add, Remove, Find

// members -- doubly linked list



class Manager
{
public:
	Manager() : activeList(new List()), reserveList(new List()) {};
	~Manager() { if (activeList) { delete activeList; } if (reserveList) { delete reserveList; } };
	Manager& operator=(const Manager&) = default;
	Manager(const Manager&) = default;

	// takes in a string and then hashes md5
	virtual snd_err privAdd(const char* input, const char* path) = 0;

	// takes in the string and hashes md5
	virtual snd_err privRemove(const char* input) = 0;

	// takes a string key and output pointer reference
	virtual snd_err privFind(const char* input, XAUDIO2_BUFFER*& out) = 0;


	// has a linked list
	List* activeList;
	List* reserveList;

private:


};


#endif // !MANAGER_H
