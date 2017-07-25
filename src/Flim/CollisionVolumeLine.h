#pragma once
#ifndef COLLISIONVOLUMELine_H
#define COLLISIONVOLUMELine_H

#include "CollisionVolumeBoundingBoxBase.h"

class Vect;
class CollisionVolume;
class CollisionVolumeBSphere;

class CollisionVolumeLine : public CollisionVolume
{
protected:
	Vect startPoint;
	Vect endPoint;

public:
	// big four
	CollisionVolumeLine() : startPoint(), endPoint() {};
	virtual ~CollisionVolumeLine()
	{
		//DebugMsg::out("CollisionVolumeLine destroyed\n");
	}
	CollisionVolumeLine(const CollisionVolumeLine&) = default;
	CollisionVolumeLine& operator=(const CollisionVolumeLine&) = default;

	//methods

	virtual errcode ComputeData(Model*, Matrix&) override = 0;
	virtual bool Intersect(const CollisionVolume&)const  override = 0;
	virtual bool Intersect(const CollisionVolumeAABB&) const override = 0;
	virtual bool Intersect(const CollisionVolumeOBB&) const override = 0;
	virtual bool Intersect(const CollisionVolumeBSphere&) const override = 0;
	virtual errcode DebugView(const Vect&) const override = 0;

};

#endif