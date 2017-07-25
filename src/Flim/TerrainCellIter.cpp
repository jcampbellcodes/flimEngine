#include "TerrainCellIter.h"
#include "TerrainCellRange.h"
TerrainCellIter::TerrainCellIter(TerrainCellRange * _range) : owner(_range)
{
	int iMin, iMax, jMin, jMax;
	owner->GetMaxMin(iMin, iMax, jMin, jMax);
	this->cell.setIndices(iMin, jMin);
	this->cell.setTerrain(owner->GetTerrain());
}

TerrainCellIter::TerrainCellIter(TerrainCellRange * _range, int i, int j) : owner(_range), cell(i,j)
{
	this->cell.setTerrain(owner->GetTerrain());
}

TerrainCellIter::TerrainCellIter(const TerrainCellIter & other) : owner(other.owner), cell(other.cell)
{
	this->cell.setTerrain(owner->GetTerrain());
}

TerrainCellIter & TerrainCellIter::operator=(const TerrainCellIter & other)
{
	this->owner = other.owner;
	this->cell = other.cell;
	return *this;
}

TerrainCellIter::~TerrainCellIter()
{
}


//  pre-increment gets indices, increments in accordance with cell range's max and min and sets cell's new indices, returns *this
TerrainCellIter & TerrainCellIter::operator++()
{
	int i, j;
	cell.getIndices(i, j);

	int iMin, iMax, jMin, jMax;
	owner->GetMaxMin(iMin, iMax, jMin, jMax);

	// increment i and j, wrap around if necessary
	if ((j + 1) > jMax) // wrap and go down a row
	{
		j = 0;
		i++;
	}
	else
	{
		j++;
	}

	cell.setIndices(i, j);
	
	return *this;
}

bool TerrainCellIter::operator!=(const TerrainCellIter & other)
{
	// check if its the same terrain; then check iters
	return !((this->owner == other.owner) && (this->getCell() == other.getCell()));
}

bool TerrainCellIter::operator==(const TerrainCellIter & other)
{
	// check if its the same terrain; then check iters
	return (this->owner == other.owner) && (this->getCell() == other.getCell());
}

bool TerrainCellIter::operator!=(TerrainCellIter & other)
{
	// check if its the same terrain; then check iters
	return !((this->owner == other.owner) && (this->getCell() == other.getCell()));
}

bool TerrainCellIter::operator==(TerrainCellIter & other)
{
	// check if its the same terrain; then check iters
	return (this->owner == other.owner) && (this->getCell() == other.getCell());
}

TerrainCell * TerrainCellIter::operator->()
{
	return &cell;
}

TerrainCell & TerrainCellIter::operator*()
{
	return cell;
}
