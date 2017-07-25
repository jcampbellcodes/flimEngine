#include "CollisionVolumeBSphere.h"
#include "Visualizer.h"
#include "MathTools.h"
#include "CollisionVolumeAABB.h"

errcode CollisionVolumeBSphere::ComputeData(Model * mod, Matrix & mat)
{
	errcode err = errcode::success;

	// Adjusting the spaceship's bounding sphere
	this->center = mod->getCenter() * mat;
	this->radius = mod->getRadius() * mat.getT().get(MatrixRowType::ROW_0).mag(); // adjust for UNIFORM scaling -- will change with scaling

	return err;
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolume & other)const
{
	return other.Intersect(*this);
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeBSphere & other)const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeAABB & other) const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeOBB & other) const
{
	return FlimMath::Intersect(*this, other);
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolumeOcclusionLine & other) const
{
	return FlimMath::Intersect(other, *this);
}

errcode CollisionVolumeBSphere::DebugView(const Vect &col) const
{
	Visualizer::ShowBSphere(*this, col);

	return errcode::success;
}

const Vect & CollisionVolumeBSphere::getCenter() const 
{
	return center;
}

float CollisionVolumeBSphere::getRadius() const
{
	return radius;
}
