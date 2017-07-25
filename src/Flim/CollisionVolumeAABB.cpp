#include "CollisionVolumeAABB.h"
#include "CollisionVolumeBSphere.h"
#include "MathTools.h"
#include "Visualizer.h"

CollisionVolumeAABB::CollisionVolumeAABB()
{
	world = Matrix(IDENTITY);
}

errcode CollisionVolumeAABB::ComputeData(Model * mod, Matrix & mat)
{
	// float
	this->scale = mat.get(MatrixRowType::ROW_0).magSqr();

	this->max = FlimMath::getMax(mod->getVectList(), mod->getVectNum(), mat);
	this->min = FlimMath::getMin(mod->getVectList(), mod->getVectNum(), mat);

	// point
	this->center = (min + max)* 0.5f;


	// VECTOR
	this->halfDiagonal = (0.5f * (this->max - this->min));
	this->halfDiagonal.set(halfDiagonal.X(), halfDiagonal.Y(), halfDiagonal.Z(), 0.0f);

	//Visualizer::ShowMarker(center);
	//Visualizer::ShowMarker(max);
	//Visualizer::ShowMarker(min);

	return errcode::success;
}

errcode CollisionVolumeAABB::SetMinMax(const Vect& _min, const Vect& _max)
{
	this->min = _min;
	this->max = _max;
	return errcode::success;  
}

bool CollisionVolumeAABB::Intersect(const CollisionVolume & other) const
{
	return other.Intersect(*this);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolumeAABB & other) const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolumeOBB & other) const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolumeBSphere & other) const
{
	return FlimMath::Intersect(other, *this);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolumeOcclusionLine & other) const
{
	return FlimMath::Intersect(other, *this);
}

errcode CollisionVolumeAABB::DebugView(const Vect & col) const
{
	Visualizer::ShowAABB(*this, col);
	return errcode::success;
}
