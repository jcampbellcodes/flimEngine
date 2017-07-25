#include "CircularData.h"

CircularData::CircularData()
	: front(CIRCULAR_DATA_SIZE),
	back(CIRCULAR_DATA_SIZE),
	empty(true),
	full(false)
{
	// initialized data
	for (int i = 0; i < CIRCULAR_DATA_SIZE; i++)
	{
		this->data[i] = {};
	}
}

CircularData::~CircularData()
{
}

bool CircularData::PushBack(ThreadCommand val)
{
	this->mtx.lock();

	bool status = true;

	// Do we have space to add?
	if (front != back || empty) 
	{
		// add data
		this->data[back.getIndex()] = val;
		back++;

		empty = false;

		// check if this add made it full
		if (front == back)
		{
			this->full = true;
		}
	}
	else
	{
		status = false;
	}

	this->mtx.unlock();

	return status;
}

bool CircularData::PopFront(ThreadCommand &val)
{
	this->mtx.lock();
	
	bool status = true;

	// Is there data to process?
	if (front != back || full)
	{
		// Grab one
		val = this->data[ front.getIndex() ] ;
		front++;

		this->full = false;

		// check if this Pop made it Empty
		if (front == back)
		{
			this->empty = true;
		}
	}
	else
	{
		status = false;
	}

	this->mtx.unlock();

	return status;
}

