#pragma once

#ifndef TERRAINCELLITER
#define TERRAINCELLITER

#include "TerrainCell.h"

// user gets first iterator from range's begin(); constructs this iterator by passing a pointer to the range



class TerrainCellRange;

// has a TerrainCellIter internally
class TerrainCellIter
{
public:
	// big four
	TerrainCellIter() = delete;
	TerrainCellIter(TerrainCellRange* _range);
	TerrainCellIter(TerrainCellRange* _range, int i, int j);
	TerrainCellIter(const TerrainCellIter&);
	TerrainCellIter& operator=(const TerrainCellIter&);
	~TerrainCellIter();

	// pre increment operator
	//  pre-increment gets indices, increments in accordance with cell range's max and min and sets cell's new indices, returns *this
	TerrainCellIter& operator++();

	// != operator --> checks both pointer to owner to see if they are compatible iterators; then checks cell's index vals
	bool operator!=(TerrainCellIter& other);
	bool operator==(TerrainCellIter& other);
	bool operator!=(const TerrainCellIter& other);
	bool operator==(const TerrainCellIter& other);

	// -> operator
	TerrainCell* operator->();

	// * operator
	TerrainCell& operator*();

private:
	// knows the container that owns it, uses that to increment and return TerrainCells
	TerrainCellRange* owner;
	TerrainCell cell;

	const TerrainCell& getCell() const { return cell; }


};
#endif