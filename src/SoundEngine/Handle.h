#pragma once
#ifndef HANDLE_H
#define HANDLE_H


class Handle
{
public:
	Handle();
	~Handle();

	Handle(const Handle&) = delete;
	Handle& operator=(const Handle&) = delete;

	// get id
	unsigned int& GetID();
	// get index
	unsigned int& GetIndex();

private:
	unsigned int ID;
	unsigned int index;

};

#endif