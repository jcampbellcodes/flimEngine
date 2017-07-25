#pragma once
#ifndef LIST_H
#define LIST_H

#include "snd_err.h"
#include "BufferNode.h"


class Node;
class BufferNode;

// Derive from List to change node types

class List
{
public:
	// big four
	List();
	~List();
	List(const List&);
	List& operator=(const List&);

	// if you have the node
	snd_err Add(Node* in);
	snd_err Remove(Node* in);

	// if you don't
	snd_err Add(unsigned int md5);
	snd_err Remove(unsigned int md5);

	snd_err Find(Node*& out, unsigned int md5);

	snd_err Print();
			
private:
	Node* head;

};


class BufferList : List
{
public:
	// big four
	BufferList();
	~BufferList();
	BufferList(const BufferList&);
	BufferList& operator=(const BufferList&);

	// if you have the node
	snd_err Add(BufferNode* in);
	snd_err Remove(BufferNode* in);

	// if you don't
	//snd_err Add(unsigned int md5);
	snd_err Remove(unsigned int md5);

	snd_err Find(BufferNode*& out, unsigned int md5);

	snd_err Print();

private:
	BufferNode* head;

};

#endif // !LIST_H
