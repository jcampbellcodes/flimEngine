#pragma once
#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "snd_err.h"
//#include <xaudio2.h>
#include "AutoXA2Include.h"
#include "Manager.h"
#include "List.h"
#include "BufferNode.h"

class BufferManager 
{
private:
	//big four and singleton
	BufferManager();
	~BufferManager();
	BufferManager(const BufferManager&) = delete;
	BufferManager& operator=(const BufferManager&) = delete;

	static BufferManager* instance;
	static BufferManager& Instance()
	{
		if (!instance)
		{
			instance = new BufferManager();
		}
		return *instance;
	}


	BufferList* activeList;
	BufferList* inactiveList;

	snd_err Load(WAVEFORMATEXTENSIBLE& _wfx, XAUDIO2_BUFFER& out, const char* path);
	// internal find
	snd_err Find(BufferNode*& out, unsigned int md5);

	// takes in a string and then hashes md5
	snd_err privAdd(const char* input, const char* path, void(*cb)(void));

	// if they have the md5
	snd_err privAdd(unsigned int input, const char * path, void(*cb)(void));

	// takes in the string and hashes md5
	snd_err privRemove(const char* input);

	// takes in md5
	snd_err privRemove(unsigned int md5);

	// takes a string key and output pointer reference
	snd_err privFind(const char* input, XAUDIO2_BUFFER*& out, WAVEFORMATEXTENSIBLE*& wfx);

	// takes an md5 key and output pointer reference
	snd_err privFind(unsigned int input, XAUDIO2_BUFFER*& out, WAVEFORMATEXTENSIBLE*& wfx);

	// clean up lists
	snd_err privTerminate();

public:

	// takes in a string and then hashes md5
	static snd_err Add(const char* input, const char* path, void(*cb)(void))
	{
		return Instance().privAdd(input, path, cb);
	}

	static snd_err Add(unsigned int input, const char* path, void(*cb)(void))
	{
		return Instance().privAdd(input, path, cb);
	}

	// takes in the string and hashes md5
	static snd_err Remove(const char* input)
	{
		return Instance().privRemove(input);
	}

	static snd_err Remove(unsigned int input)
	{
		return Instance().privRemove(input);
	}

	// takes a string key and output pointer reference
	static snd_err Find(const char* input, XAUDIO2_BUFFER*& out, WAVEFORMATEXTENSIBLE*& wfx)
	{
		return Instance().privFind(input, out, wfx);
	}

	static snd_err Find(unsigned int input, XAUDIO2_BUFFER*& out, WAVEFORMATEXTENSIBLE*& wfx)
	{
		return Instance().privFind(input, out, wfx);
	}

	static snd_err Terminate()
	{
		return Instance().privTerminate();
	}



};


#endif // 
