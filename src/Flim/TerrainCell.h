#pragma once
#ifndef TERRAINCELL
#define TERRAINCELL
#include "err.h"
#include "CollisionVolumeAABB.h"
class FlimTerrain;

class TerrainCell : public Align16
{
public:

	// big four
	TerrainCell();
	TerrainCell(int _i, int _j);
	TerrainCell(const TerrainCell&);
	TerrainCell& operator=(const TerrainCell&);
	~TerrainCell() = default;

	// getAABB() -> querys terrain for AABB based on its indices
	CollisionVolumeAABB& getAABB();


	// get/set indices
	errcode getIndices(int& _i, int& _j) const;
	bool operator==(const TerrainCell & other) const;
	errcode setIndices(int _i, int _j);
	errcode setTerrain(FlimTerrain* t) { terrain = t; return errcode::success; };

private:
	int i;
	int j;
	CollisionVolumeAABB aabb;
	FlimTerrain* terrain;

};

#endif