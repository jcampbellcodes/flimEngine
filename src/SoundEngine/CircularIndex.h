#ifndef FRONT_INDEX_H
#define FRONT_INDEX_H

#include <assert.h>

class CircularIndex
{
public:
	CircularIndex(int buffSize)
	{
		this->size = buffSize;
		this->mask = buffSize - 1;
		this->index = 0;
	}

	CircularIndex() = delete;
	CircularIndex(const CircularIndex &) = delete;
	const CircularIndex &operator = (const CircularIndex &) = delete;
	~CircularIndex() = default;

	// postfix
	int operator++(int)
	{
		this->index++;

		// Circular 
		this->index = this->index & this->mask;

		return this->index;
	}

	bool operator==(const CircularIndex &tmp)
	{
		assert(this->size == tmp.size);
		return (this->index == tmp.index);
	}

	bool operator!=(const CircularIndex &tmp)
	{
		assert(this->size == tmp.size);
		return (this->index != tmp.index);
	}

	int getIndex() const
	{
		return this->index;
	}

private:
	int index;
	int size;
	unsigned int mask;
};

#endif
