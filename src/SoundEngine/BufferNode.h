#pragma once
#ifndef BufferNode_H
#define BufferNode_H

// BufferNode base class
// next, prev

// classes inherit to store data members
#include "snd_err.h"
//#include <xaudio2.h>
#include "AutoXA2Include.h"
#include "AzulCore.h"

class BufferList;
class BufferManager;

class BufferNode
{
public:
	BufferNode() = delete;
	//BufferNode(unsigned int md5, XAUDIO2_BUFFER buffer, WAVEFORMATEXTENSIBLE _wfx);
	BufferNode(unsigned int md5);
	~BufferNode()
	{
		//DebugMsg::out("buffer node cleaned\n");
	}
	BufferNode(const BufferNode&) = default;
	BufferNode& operator=(const BufferNode&) = default;

	snd_err GetNext(BufferNode* out);
	snd_err SetNext(BufferNode* in);

	snd_err GetPrev(BufferNode * out);

	snd_err SetPrev(BufferNode * in);

	snd_err GetData(unsigned int& out);
	snd_err SetData(unsigned int in);


	snd_err InitializeData(XAUDIO2_BUFFER* buf, WAVEFORMATEXTENSIBLE* _wfx);


	//reference counting
	snd_err AddRef();
	snd_err RemoveRef();
	snd_err InUse();

private:
	BufferNode* next;
	BufferNode* prev;

	unsigned int data; // MD5 resource tag
	XAUDIO2_BUFFER* buffer;
	WAVEFORMATEXTENSIBLE* wfx;
	unsigned int refCount;
	friend class BufferList;
	friend class BufferManager;

};


#endif