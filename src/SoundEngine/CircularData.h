#ifndef CIRCULAR_DATA_H
#define CIRCULAR_DATA_H

#include "CircularIndex.h"
#include "SoundCallRegistry.h"
#include "ThreadCommands.h"
#include <mutex>

const int CIRCULAR_DATA_SIZE = 256;



class CircularData
{
public:
	CircularData();
	
	CircularData(const CircularData &) = delete;
	const CircularData &operator = (const CircularData &) = delete;
	~CircularData();

	bool PushBack(ThreadCommand val);
	bool PopFront(ThreadCommand &val);

private:
	ThreadCommand data[CIRCULAR_DATA_SIZE];

	CircularIndex front;
	CircularIndex back;
	bool empty;
	bool full;

	std::mutex mtx;
};

#endif
