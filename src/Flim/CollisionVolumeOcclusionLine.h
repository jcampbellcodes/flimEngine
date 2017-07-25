#pragma once
#ifndef CollisionVolumeOcclusionLine_H
#define CollisionVolumeOcclusionLine_H

#include "CollisionVolumeLine.h"
class Vect;
class CollisionVolume;
class CollisionVolumeBSphere;

class CollisionVolumeOcclusionLine : public CollisionVolumeLine
{
private:

public:
	// big four
	CollisionVolumeOcclusionLine(){};
	virtual ~CollisionVolumeOcclusionLine()
	{
		//DebugMsg::out("CollisionVolumeOcclusionLine destroyed\n");
	}
	CollisionVolumeOcclusionLine(const CollisionVolumeOcclusionLine&) = default;
	CollisionVolumeOcclusionLine& operator=(const CollisionVolumeOcclusionLine&) = default;

	//methods
	Vect getStartPoint() const { return startPoint; };
	Vect getEndPoint() const { return endPoint; };
	virtual errcode ComputeData(Model*, Matrix&) override;
	virtual bool Intersect(const CollisionVolume&)const  override;
	virtual bool Intersect(const CollisionVolumeAABB&) const override;
	virtual bool Intersect(const CollisionVolumeOBB&) const override;
	virtual bool Intersect(const CollisionVolumeBSphere&) const override;
	virtual bool Intersect(const CollisionVolumeOcclusionLine&) const override;
	virtual errcode DebugView(const Vect&) const override;

};

#endif