#include "CollisionVolumeOBB.h"
#include "CollisionVolumeBSphere.h"
#include "MathTools.h"
#include "Visualizer.h"

CollisionVolumeOBB::CollisionVolumeOBB(Model* mod)
{
	// point
	this->max = mod->getMaxAABB();

	// point
	this->min = mod->getMinAABB();

	// VECTOR
	this->halfDiagonal = 0.5f * (this->max - this->min);
	this->halfDiagonal.set(halfDiagonal.X(), halfDiagonal.Y(), halfDiagonal.Z(), 0.0f);


}

errcode CollisionVolumeOBB::ComputeData(Model * , Matrix & mat)
{
	world = mat;

	// float
	this->scale = mat.get(MatrixRowType::ROW_0).magSqr();

	// point
	this->center = ((min + max) * 0.5f) * mat;

	return errcode::success;
}

bool CollisionVolumeOBB::Intersect(const CollisionVolume & other) const
{
	return other.Intersect(*this);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolumeOBB & other) const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolumeAABB & other) const
{
	return FlimMath::Intersect(other, *this);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolumeBSphere & other) const
{
	return FlimMath::Intersect(other, *this);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolumeOcclusionLine & other) const
{
	return FlimMath::Intersect(other, *this);
}

errcode CollisionVolumeOBB::DebugView(const Vect & col) const
{
	Visualizer::ShowOBB(world, *this, col);
	return errcode::success;
}
