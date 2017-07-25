#include "BufferNode.h"

//BufferNode::BufferNode(unsigned int md5, XAUDIO2_BUFFER buf, WAVEFORMATEXTENSIBLE _wfx) : next(nullptr), prev(nullptr), data(md5), buffer(buf), wfx(_wfx), refCount(0) {}

BufferNode::BufferNode(unsigned int md5) : next(nullptr), prev(nullptr), data(md5), buffer(nullptr), wfx(nullptr), refCount(0) {}

snd_err BufferNode::GetNext(BufferNode * out)
{
	snd_err err;
	if (next)
	{
		err = snd_err::OK;
	}
	else
	{
		err = snd_err::NULLPTR;
	}

	out = next;
	return err;
}
snd_err BufferNode::SetNext(BufferNode * in)
{
	snd_err err;
	if (in)
	{
		err = snd_err::OK;
	}
	else
	{
		err = snd_err::NULLPTR;
	}

	next = in;

	return err;
}

snd_err BufferNode::GetPrev(BufferNode * out)
{
	snd_err err;
	if (prev)
	{
		err = snd_err::OK;
	}
	else
	{
		err = snd_err::NULLPTR;
	}

	out = prev;
	return err;
}
snd_err BufferNode::SetPrev(BufferNode * in)
{
	snd_err err;
	if (in)
	{
		err = snd_err::OK;
	}
	else
	{
		err = snd_err::NULLPTR;
	}

	prev = in;

	return err;
}

snd_err BufferNode::GetData(unsigned int & out)
{
	snd_err err = snd_err::OK;

	out = data;

	return err;
}

snd_err BufferNode::SetData(unsigned int in)
{
	snd_err err = snd_err::OK;

	data = in;

	return err;
}

snd_err BufferNode::InitializeData(XAUDIO2_BUFFER * buf, WAVEFORMATEXTENSIBLE * _wfx)
{
	this->buffer = buf;
	this->wfx = _wfx;
	return snd_err::OK;
}

snd_err BufferNode::AddRef()
{

	refCount++;
	//DebugMsg::out("BufferNode: Buffer reference added:%u   Buffer RefCount:%u\n", data, refCount);
	return snd_err::OK;
}

snd_err BufferNode::RemoveRef()
{

	refCount--;
	//DebugMsg::out("BufferNode: Buffer reference removed:%u   Buffer RefCount:%u\n", data, refCount);
	return snd_err::OK;
}

snd_err BufferNode::InUse()
{
	snd_err err;
	if (refCount <= 0)
	{
		err = snd_err::NOT_IN_USE;
	}
	else
	{
		err = snd_err::IN_USE;
	}
	return err;
}


