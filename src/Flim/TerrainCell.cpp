#include "TerrainCell.h"
#include "Terrain.h"

TerrainCell::TerrainCell() : terrain(nullptr), aabb()
{
}

TerrainCell::TerrainCell(int _i, int _j) : i(_i), j(_j), terrain(nullptr), aabb()
{
}

TerrainCell::TerrainCell(const TerrainCell & other) : i(other.i), j(other.j), terrain(other.terrain), aabb()
{
}

TerrainCell & TerrainCell::operator=(const TerrainCell & o)
{
	i = o.i;
	j = o.j;
	terrain = o.terrain;
	aabb = o.aabb;

	return *this;
}

CollisionVolumeAABB & TerrainCell::getAABB()
{
	Vect min, max;
	terrain->FindMin(i, j, min);
	terrain->FindMax(i, j, max);

	aabb.SetMinMax(min, max);

	return aabb;
}

errcode TerrainCell::getIndices(int & _i, int & _j) const
{
	_i = i;
	_j = j;
	return errcode::success;
}

bool TerrainCell::operator==(const TerrainCell& other) const
{
	return (this->i == other.i) && (this->j == other.j);
}

errcode TerrainCell::setIndices(int _i, int _j)
{
	i = _i;
	j = _j;
	return errcode::success;
}
