#pragma once
#ifndef TERRAIN_CELLRANGE
#define TERRAIN_CELLRANGE

#include "err.h"
#include "TerrainCellIter.h"

// signal flow:
// user creates terraincellrange with TerrainPointer and collidable's BSphere
// terraincellrange calculates max and min index pairs

// user gets the first iterator via begin; begin constructs an iterator with TerrainCell(iMin, jMin) and returns
// checks against end, which is TerrainCell(iMax, jMax)

// user refers to iterator or operations

class FlimTerrain;
class TerrainCell;
class CollisionVolumeBSphere;

// owner of iterators

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	TerrainCellRange
///
/// \brief	A terrain cell range.
///
/// \author	Jack Campbell
/// \date	6/1/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class TerrainCellRange
{
public:

	// big four
	TerrainCellRange() = delete;
	TerrainCellRange(FlimTerrain* terrain, const CollisionVolumeBSphere& bsphere); // TODO -- add more options for constructing range; aabb, radius/center, collidable, etc
	TerrainCellRange(const TerrainCellRange&) = default;
	TerrainCellRange& operator=(const TerrainCellRange&) = default;
	~TerrainCellRange();
	

	// begin()

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	TerrainCellIter& TerrainCellRange::begin();
	///
	/// \brief	Gets the begin.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	A reference to a TerrainCellIter.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	TerrainCellIter& begin();

	// end()

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	TerrainCellIter& TerrainCellRange::end();
	///
	/// \brief	Gets the end.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	A reference to a TerrainCellIter.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	TerrainCellIter& end();


private:
	FlimTerrain* pTerrain;

	TerrainCellIter _begin;
	TerrainCellIter _end;

	int iMin;
	int iMax;
	int jMin;
	int jMax;

	friend class TerrainCellIter;
	errcode GetMaxMin(int& _iMin, int& iMax, int& jMin, int& jMax) const;
	FlimTerrain* GetTerrain() const;


};

#endif