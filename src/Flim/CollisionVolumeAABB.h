#pragma once
#ifndef COLLISIONVOLUMEAABB_H
#define COLLISIONVOLUMEAABB_H

#include "CollisionVolumeBoundingBoxBase.h"

class Vect;
class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeOcclusionLine;

class CollisionVolumeAABB : public CollisionVolumeBoundingBoxBase
{
public:
	// big four
	CollisionVolumeAABB();
	~CollisionVolumeAABB()
	{
		//DebugMsg::out("CollisionVolumeAABB destroyed\n");
	}
	CollisionVolumeAABB(const CollisionVolumeAABB&) = default;
	CollisionVolumeAABB& operator=(const CollisionVolumeAABB&) = default;

	//methods

	errcode ComputeData(Model* , Matrix&) override;
	errcode SetMinMax(const Vect& min, const Vect& max);
	bool Intersect(const CollisionVolume& )const  override;
	bool Intersect(const CollisionVolumeAABB& ) const override;
	bool Intersect(const CollisionVolumeOBB&) const override;
	bool Intersect(const CollisionVolumeBSphere& ) const override;
	bool Intersect(const CollisionVolumeOcclusionLine&) const override;
	errcode DebugView(const Vect&) const override;

};

#endif