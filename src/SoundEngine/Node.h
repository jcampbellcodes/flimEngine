#pragma once
#ifndef NODE_H
#define NODE_H

// node base class
// next, prev

// classes inherit to store data members
#include "snd_err.h"
#include "AzulCore.h"
class Node
{
public:
	Node() = delete;
	Node(unsigned int md5);
	~Node()
	{
		DebugMsg::out("Node cleaned\n");
	};
	Node(const Node&) = default;
	Node& operator=(const Node&) = default;

	snd_err GetNext(Node* out);
	snd_err SetNext(Node* in);

	snd_err GetPrev(Node * out);

	snd_err SetPrev(Node * in);

	snd_err GetData(unsigned int& out);
	snd_err SetData(unsigned int in);

private:
	Node* next;
	Node* prev;

	unsigned int data; // MD5 resource tag
	friend class List;

};


#endif