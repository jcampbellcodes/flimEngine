#include "Node.h"

Node::Node(unsigned int md5) : next(nullptr), prev(nullptr), data(md5) {}

snd_err Node::GetNext(Node * out)
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
snd_err Node::SetNext(Node * in)
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

snd_err Node::GetPrev(Node * out)
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
snd_err Node::SetPrev(Node * in)
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

snd_err Node::GetData(unsigned int & out)
{
	snd_err err = snd_err::OK;

	out = data;

	return err;
}

snd_err Node::SetData(unsigned int in)
{
	snd_err err = snd_err::OK;

	data = in;

	return err;
}


