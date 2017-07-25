#include "SoundList.h"
#include "SoundNode.h"
#include "AzulCore.h"
#include <assert.h>

/**********************************/
/*           SoundList            */
/**********************************/


SoundList::SoundList() : head(nullptr)
{
}

SoundList::~SoundList()
{
	// iterate through and delete 'em
	SoundNode* iter = head;
	SoundNode* toDelete = nullptr;

	while (iter)
	{
		// copy
		toDelete = iter;
		// get outta the way
		iter = iter->next;
		// kill it
		delete toDelete;
	}
	head = nullptr;
	DebugMsg::out("SoundList Cleaned\n");
};

SoundList::SoundList(const SoundList &) = default;

SoundList & SoundList::operator=(const SoundList &) = default;


snd_err SoundList::Remove(unsigned int md5)
{
	snd_err err = snd_err::ERR;
	SoundNode* iter = nullptr;
	err = Find(iter, md5);

	Remove(iter);

	assert(!iter);
	err = snd_err::OK;
	return err;
}


snd_err SoundList::Remove(Sound* snd)
{
	snd_err err = snd_err::ERR;
	SoundNode* iter = nullptr;
	err = Find(iter, snd);

	Remove(iter);

	assert(!iter);
	err = snd_err::OK;
	return err;
}

snd_err SoundList::Find(SoundNode *& out, Sound* snd)
{
	snd_err err = snd_err::NOT_FOUND;

	SoundNode* iter = head;
	while (iter)
	{
		if (iter->data.sound == snd)
		{
			out = iter;
			err = snd_err::OK;
			return err;
		}
		iter = iter->next;
	}

	return err;
}

snd_err SoundList::Find(SoundNode *& out, unsigned int md5)
{
	snd_err err = snd_err::NOT_FOUND;

	SoundNode* iter = head;
	while (iter)
	{
		if (iter->data.md5 == md5)
		{
			out = iter;
			err = snd_err::OK;
			return err;
		}
		iter = iter->next;
	}

	return err;
}

snd_err SoundList::Print()
{
	SoundNode* iter = head;

	DebugMsg::out("\n\n\nthe SoundList!\n\n");

	while (iter)
	{
		DebugMsg::out("Data:%x \n", iter->data);
		iter = iter->next;
	}
	DebugMsg::out("\n\n\n that's the SoundList!\n\n");


	return snd_err::OK;
}




// dummies
snd_err SoundList::Add(SoundNode * in)
{
	snd_err err = snd_err::ERR;

	if (!head) // initialize SoundList
	{
		// tell the SoundList that this SoundNode is the head
		head = in;
		// assert next and prev are null
		assert(!in->next);
		assert(!in->prev);
		err = snd_err::OK;

	}
	else // there's a head, reassign it
	{
		// push front
		// set its next to head, set head's prev to new SoundNode
		in->SetNext(head);
		head->SetPrev(in);
		// tell new SoundNode it is head now (sorry, old head!)
		head = in;
		assert(!head->prev);
		assert(head->next);
		err = snd_err::OK;
	}

	return err;
}

snd_err SoundList::Remove(SoundNode * in)
{
	snd_err err = snd_err::ERR;

	if (!in)
	{
		err = snd_err::NOT_FOUND;
		return err;
	}

	assert(in);


	// so it's there, but...
	if (in->next && !in->prev) // it's the head
	{
		assert(in == head);
		in->next->prev = nullptr;
		head = in->next;
		delete in;
		in = nullptr;
	}
	else if (in->prev && !in->next) // it's the last SoundNode
	{
		in->prev->next = nullptr;
		delete in;
		in = nullptr;
	}
	else if (!in->prev && !in->next) // it's the only SoundNode
	{
		delete in;
		in = nullptr;
		head = nullptr;
	}
	else // it's in the middle
	{
		in->prev->next = in->next;
		in->next->prev = in->prev;
		delete in;
		in = nullptr;
	}

	assert(!in);
	err = snd_err::OK;
	return err;
}




