#include "List.h"
#include "Node.h"
#include "AzulCore.h"
#include <assert.h>

List::List() : head(nullptr)
{
}

List::~List()
{
	// iterate through and delete 'em
	Node* iter = head;
	Node* toDelete = nullptr;

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
	//DebugMsg::out("List cleaned\n");
};

List::List(const List &) = default;

List & List::operator=(const List &) = default;


snd_err List::Add(unsigned int md5)
{
	snd_err err = snd_err::ERR;

	if (!head) // initialize list
	{
		// make a node
		Node* newNode = new Node(md5);
		// tell the list that this node is the head
		head = newNode;
		// assert next and prev are null
		assert(!newNode->next);
		assert(!newNode->prev);
		err = snd_err::OK;

	}
	else // there's a head, reassign it
	{
		// make a new node
		Node* newNode = new Node(md5);
		// push front
		// set its next to head, set head's prev to new node
		newNode->SetNext(head);
		head->SetPrev(newNode);
		// tell new node it is head now (sorry, old head!)
		head = newNode;
		assert(!head->prev);
		assert(head->next);
		err = snd_err::OK;
	}

	return err;
}

snd_err List::Remove(unsigned int md5)
{
	snd_err err = snd_err::ERR;
	Node* iter = nullptr;
	err = Find(iter, md5);

	Remove(iter);

	assert(!iter);
	err = snd_err::OK;
	return err;
}

snd_err List::Find(Node *& out, unsigned int md5)
{
	snd_err err = snd_err::NOT_FOUND;

	Node* iter = head;
	while (iter)
	{
		if (iter->data == md5)
		{
			out = iter;
			err = snd_err::OK;
			return err;
		}
		iter = iter->next;
	}

	return err;
}

snd_err List::Print()
{
	Node* iter = head;

	DebugMsg::out("\n\n\nthe list!\n\n");

	while (iter)
	{
		DebugMsg::out("Data:%x \n", iter->data);
		iter = iter->next;
	}
	DebugMsg::out("\n\n\n that's the list!\n\n");


	return snd_err::OK;
}



// dummies
snd_err List::Add(Node * in)
{
	snd_err err = snd_err::ERR;

	if (!head) // initialize list
	{
		// tell the list that this node is the head
		head = in;
		// assert next and prev are null
		assert(!in->next);
		assert(!in->prev);
		err = snd_err::OK;

	}
	else // there's a head, reassign it
	{
		// push front
		// set its next to head, set head's prev to new node
		in->SetNext(head);
		head->SetPrev(in);
		// tell new node it is head now (sorry, old head!)
		head = in;
		assert(!head->prev);
		assert(head->next);
		err = snd_err::OK;
	}

	return err;
}

snd_err List::Remove(Node * in)
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
	else if (in->prev && !in->next) // it's the last node
	{
		in->prev->next = nullptr;
		delete in;
		in = nullptr;
	}
	else if (!in->prev && !in->next) // it's the only node
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





/**********************************/
/*           BUFFER LIST          */
/**********************************/


BufferList::BufferList() : head(nullptr)
{
}

BufferList::~BufferList()
{
	// iterate through and delete 'em
	BufferNode* iter = head;
	BufferNode* toDelete = nullptr;

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
};

BufferList::BufferList(const BufferList &) = default;

BufferList & BufferList::operator=(const BufferList &) = default;


snd_err BufferList::Remove(unsigned int md5)
{
	snd_err err = snd_err::ERR;
	BufferNode* iter = nullptr;
	err = Find(iter, md5);

	Remove(iter);

	assert(!iter);
	err = snd_err::OK;
	return err;
}

snd_err BufferList::Find(BufferNode *& out, unsigned int md5)
{
	snd_err err = snd_err::NOT_FOUND;

	BufferNode* iter = head;
	while (iter)
	{
		if (iter->data == md5)
		{
			out = iter;
			err = snd_err::OK;
			return err;
		}
		iter = iter->next;
	}

	return err;
}

snd_err BufferList::Print()
{
	BufferNode* iter = head;

	DebugMsg::out("\n\n\nthe BufferList!\n\n");

	while (iter)
	{
		DebugMsg::out("Data:%x \n", iter->data);
		iter = iter->next;
	}
	DebugMsg::out("\n\n\n that's the BufferList!\n\n");


	return snd_err::OK;
}




// dummies
snd_err BufferList::Add(BufferNode * in)
{
	snd_err err = snd_err::ERR;
	in->next = nullptr;
	in->prev = nullptr;
	if (!head) // initialize BufferList
	{
		// tell the BufferList that this BufferNode is the head
		head = in;
		// assert next and prev are null
		assert(!in->next);
		assert(!in->prev);
		err = snd_err::OK;

	}
	else // there's a head, reassign it
	{
		// push front
		// set its next to head, set head's prev to new BufferNode
		in->SetNext(head);
		head->SetPrev(in);
		// tell new BufferNode it is head now (sorry, old head!)
		head = in;
		assert(!head->prev);
		assert(head->next);
		err = snd_err::OK;
	}

	return err;
}

snd_err BufferList::Remove(BufferNode * in)
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
	else if (in->prev && !in->next) // it's the last BufferNode
	{
		in->prev->next = nullptr;
		delete in;
		in = nullptr;
	}
	else if (!in->prev && !in->next) // it's the only BufferNode
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




