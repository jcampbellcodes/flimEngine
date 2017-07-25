#pragma once
#ifndef COLLISIONVOLUMEOBB_H
#define COLLISIONVOLUMEOBB_H

#include "CollisionVolumeBoundingBoxBase.h"
class Vect;
class CollisionVolume;
class CollisionVolumeBSphere;

class CollisionVolumeOBB : public CollisionVolumeBoundingBoxBase
{
public:
	// big four
	CollisionVolumeOBB(Model* mod);
	~CollisionVolumeOBB()
	{
		//DebugMsg::out("CollisionVolumeOBB destroyed\n");
	}
	CollisionVolumeOBB(const CollisionVolumeOBB&) = default;
	CollisionVolumeOBB& operator=(const CollisionVolumeOBB&) = default;

	//methods

	errcode ComputeData(Model*, Matrix&) override;
	bool Intersect(const CollisionVolume&)const  override;
	bool Intersect(const CollisionVolumeOBB&) const override;
	bool Intersect(const CollisionVolumeAABB&) const override;
	bool Intersect(const CollisionVolumeBSphere&) const override;
	bool Intersect(const CollisionVolumeOcclusionLine&) const override;
	errcode DebugView(const Vect&) const override;

};

#endif