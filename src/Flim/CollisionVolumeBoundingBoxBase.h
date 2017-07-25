#pragma once
#ifndef COLLISIONVOLUMEBoundingBoxBase_H
#define COLLISIONVOLUMEBoundingBoxBase_H

#include "CollisionVolume.h"

class CollisionVolumeBoundingBoxBase : public CollisionVolume
{
public:
	// big four
	CollisionVolumeBoundingBoxBase() = default;
	virtual ~CollisionVolumeBoundingBoxBase()
	{
		//DebugMsg::out("CollisionVolumeBoundingBoxBase destroyed\n");
	}
	CollisionVolumeBoundingBoxBase(const CollisionVolumeBoundingBoxBase&) = default;
	CollisionVolumeBoundingBoxBase& operator=(const CollisionVolumeBoundingBoxBase&) = default;

	//methods

	virtual errcode ComputeData(Model*, Matrix&) override = 0;
	virtual bool Intersect(const CollisionVolume&)const  override = 0;
	virtual bool Intersect(const CollisionVolumeAABB&) const = 0;
	virtual bool Intersect(const CollisionVolumeOBB&) const = 0;
	virtual bool Intersect(const CollisionVolumeBSphere&) const = 0;
	virtual bool Intersect(const CollisionVolumeOcclusionLine&) const = 0;
	errcode DebugView(const Vect&) const override = 0;

	// acc
	// essors
	const Vect& getMin() const { return min; };
	const Vect& getMax() const { return max; };

	const Matrix& getWorld() const { return world; };
	const Vect& getHalfDiagonal() const { return halfDiagonal; };
	float getScaleSquared() const { return scale; };
	const Vect& getCenter() const { return center; };

protected:

	Vect max;
	Vect min;


	Matrix world;
	Vect center; // point
	Vect halfDiagonal; // vect
	float scale;

private:


};

#endif