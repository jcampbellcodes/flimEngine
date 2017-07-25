#include "SoundNode.h"
#include "Sound.h"

SoundNode::SoundNode(unsigned int _md5, Sound* _sound) : next(nullptr), prev(nullptr) 
{
	this->data.md5 = _md5;
	this->data.sound = _sound;
}

SoundNode::~SoundNode()
{
	delete data.sound;
	//DebugMsg::out("Sound node cleaned\n");
}

snd_err SoundNode::GetNext(SoundNode * out)
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
snd_err SoundNode::SetNext(SoundNode * in)
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

snd_err SoundNode::GetPrev(SoundNode * out)
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
snd_err SoundNode::SetPrev(SoundNode * in)
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

snd_err SoundNode::GetData(SoundData & out)
{
	snd_err err = snd_err::OK;

	out = data;

	return err;
}

snd_err SoundNode::SetData(SoundData& in)
{
	snd_err err = snd_err::OK;

	data = in;

	return err;
}


