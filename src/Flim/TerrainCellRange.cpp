#include "TerrainCellRange.h"

#include "Terrain.h"

TerrainCellRange::TerrainCellRange(FlimTerrain * terrain, const CollisionVolumeBSphere & bsphere) : pTerrain(terrain), _begin(this), _end(this)
{
	// 1: Generate 'AABB' from BSphere (just max/min vect)

	Vect maxBS = Vect(bsphere.getCenter().X() + bsphere.getRadius(), bsphere.getCenter().Y() + bsphere.getRadius(), bsphere.getCenter().Z() + bsphere.getRadius());
	Vect minBS = Vect(bsphere.getCenter().X() - bsphere.getRadius(), bsphere.getCenter().Y() - bsphere.getRadius(), bsphere.getCenter().Z() - bsphere.getRadius());

	// 2: Get iMax, jMax, iMin, jMin
	
	iMax = static_cast<int>(abs(maxBS.Z() / terrain->getCellDimension()));
	jMax = static_cast<int>(abs(maxBS.X() / terrain->getCellDimension()));
	iMin = static_cast<int>(abs(minBS.Z() / terrain->getCellDimension()));
	jMin = static_cast<int>(abs(minBS.X() / terrain->getCellDimension()));

	_begin = TerrainCellIter(this, iMin, jMin);
	_end = TerrainCellIter(this, iMax, jMax);

}

TerrainCellRange::~TerrainCellRange()
{
}

TerrainCellIter & TerrainCellRange::begin()
{
	return _begin;
}

TerrainCellIter & TerrainCellRange::end()
{
	return _end;
}

errcode TerrainCellRange::GetMaxMin(int & _iMin, int & _iMax, int & _jMin, int & _jMax) const
{
	_iMin = iMin;
	_iMax = iMax;
	_jMin = jMin;
	_jMax = jMax;
	return errcode::success;
}

FlimTerrain * TerrainCellRange::GetTerrain() const
{
	return this->pTerrain;
}
