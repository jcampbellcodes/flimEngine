#include "CollisionVolumeOcclusionLine.h"
#include "Visualizer.h"
#include "..\SoundEngine\FlimListener.h"
#include "MathTools.h"
errcode CollisionVolumeOcclusionLine::ComputeData(Model *, Matrix & mat)
{
	// get end position from flim listener
	this->endPoint = FlimListener::GetPosition();

	// get start position from trans matrix
	this->startPoint = mat.get(MatrixRowType::ROW_3);

	return errcode::success;
}

bool CollisionVolumeOcclusionLine::Intersect(const CollisionVolume & other) const
{
	return other.Intersect(*this);
}

bool CollisionVolumeOcclusionLine::Intersect(const CollisionVolumeOBB & other) const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeOcclusionLine::Intersect(const CollisionVolumeAABB & other) const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeOcclusionLine::Intersect(const CollisionVolumeBSphere & other) const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeOcclusionLine::Intersect(const CollisionVolumeOcclusionLine & other ) const
{
	return FlimMath::Intersect(*this, other);
}

errcode CollisionVolumeOcclusionLine::DebugView(const Vect & col) const
{
	Visualizer::ShowLine(this->startPoint, this->endPoint, col);
	return errcode::success;
}