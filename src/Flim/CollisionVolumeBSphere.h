#pragma once
#ifndef COLLISIONVOLUMEBSPHERE_H
#define COLLISIONVOLUMEBSPHERE_H

#include "CollisionVolume.h"

class Vect;
class CollisionVolumeAABB;

class CollisionVolumeBSphere : public CollisionVolume
{
public:
	// big four
	CollisionVolumeBSphere() = default;
	~CollisionVolumeBSphere()
	{
		//DebugMsg::out("CollisionVolumeBSphere destroyed\n");
	}
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = default;
	CollisionVolumeBSphere& operator=(const CollisionVolumeBSphere&) = default;

	//methods

	errcode ComputeData(Model* mod, Matrix& mat) override;
	bool Intersect(const CollisionVolume& other) const override;
	bool Intersect(const CollisionVolumeBSphere& other) const;
	bool Intersect(const CollisionVolumeAABB& other) const;
	bool Intersect(const CollisionVolumeOBB& other) const;
	bool Intersect(const CollisionVolumeOcclusionLine& other) const;

	errcode DebugView(const Vect&) const override;

	// accessors
	const Vect& getCenter() const;
	float getRadius() const;

private:

	Vect center;
	float radius;


};

#endif