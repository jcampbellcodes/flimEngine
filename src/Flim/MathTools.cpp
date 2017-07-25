#include "MathTools.h"
#include "CollisionVolume.h"
#include "CollisionVolumeAABB.h"
#include "Collidable.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeOBB.h"
#include <assert.h>

bool FlimMath::Intersect(const CollisionVolumeBSphere & A, const CollisionVolumeBSphere & B)
{
	Vect cDiff(A.getCenter() - B.getCenter()); // C - C'

	// sanity check
	assert(cDiff.X() == (A.getCenter() - B.getCenter()).X());
	assert(cDiff.Y() == (A.getCenter() - B.getCenter()).Y());
	assert(cDiff.Z() == (A.getCenter() - B.getCenter()).Z());

	const float r_sqr_dist = (A.getRadius() + B.getRadius()) * (A.getRadius() + B.getRadius()); // (r + r')^2

	if (cDiff.dot(cDiff) < r_sqr_dist) // (C - C') dot (C - C') < (r + r')^2 
	{
		return true;
	}

	return false;
}

bool FlimMath::Intersect(const CollisionVolumeBSphere & A, const Vect & P)
{
	Vect cDiff(P - A.getCenter());
	const float r_sqr = A.getRadius() * A.getRadius();

	if (cDiff.dot(cDiff) < r_sqr) // (P - C) dot (P - C) < r^2 
	{
		return true;
	}

	return false;
}


Vect FlimMath::ClampPoint(Vect & point, const Vect& min, const Vect& max)
{
	// get clamped point by clamping component to [max, min] on all three axes
	float x = ClampFloat(point.X(), min.X(), max.X());
	float y = ClampFloat(point.Y(), min.Y(), max.Y());
	float z = ClampFloat(point.Z(), min.Z(), max.Z());

	return Vect(x, y, z);
}


bool FlimMath::Intersect(const CollisionVolumeBSphere & A, const CollisionVolumeAABB & B)
{
	// get clamped point by clamping component to [max, min] on all three axes
	float x = ClampFloat(A.getCenter().X(), B.getMin().X(), B.getMax().X());
	float y = ClampFloat(A.getCenter().Y(), B.getMin().Y(), B.getMax().Y());
	float z = ClampFloat(A.getCenter().Z(), B.getMin().Z(), B.getMax().Z());


	// test this point for intersection with bsphere
	// if(P - C) dot (P - C) < r^2
	const Vect P(x, y, z);
	return Intersect(A, P);
}

bool FlimMath::Intersect(const CollisionVolumeBSphere & bs, const CollisionVolumeOBB & obb)
{
	// move BS center to OBB local space; C' = W-1(C)
	Vect c_prime = bs.getCenter() * obb.getWorld().getInv();
	// Clamp C' to OBB in LOCAL space
	Vect q = ClampPoint(c_prime, obb.getMin(), obb.getMax());
	// Move clamped C' to world space via W(Clamped C')
	Vect q_prime = q * obb.getWorld();
	// test if clamped C' is inside BS
	return Intersect(bs, q_prime);
}


bool FlimMath::Intersect(const CollisionVolumeAABB & M, const CollisionVolumeOBB & N)
{

	return
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_0), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_1), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_2), M, N) &&
		OBBOverlap(N.getWorld().get(MatrixRowType::ROW_0), M, N) &&
		OBBOverlap(N.getWorld().get(MatrixRowType::ROW_1), M, N) &&
		OBBOverlap(N.getWorld().get(MatrixRowType::ROW_2), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_0).cross(N.getWorld().get(MatrixRowType::ROW_0)), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_0).cross(N.getWorld().get(MatrixRowType::ROW_1)), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_0).cross(N.getWorld().get(MatrixRowType::ROW_2)), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_1).cross(N.getWorld().get(MatrixRowType::ROW_0)), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_1).cross(N.getWorld().get(MatrixRowType::ROW_1)), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_1).cross(N.getWorld().get(MatrixRowType::ROW_2)), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_2).cross(N.getWorld().get(MatrixRowType::ROW_0)), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_2).cross(N.getWorld().get(MatrixRowType::ROW_1)), M, N) &&
		OBBOverlap(M.getWorld().get(MatrixRowType::ROW_2).cross(N.getWorld().get(MatrixRowType::ROW_2)), M, N);
}

bool FlimMath::Intersect(const CollisionVolumeOBB & M, const CollisionVolumeOBB & N)
{
	return 
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_0), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_1), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_2), M, N)&&
	OBBOverlap(N.getWorld().get(MatrixRowType::ROW_0), M, N)&&
	OBBOverlap(N.getWorld().get(MatrixRowType::ROW_1), M, N)&&
	OBBOverlap(N.getWorld().get(MatrixRowType::ROW_2), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_0).cross(N.getWorld().get(MatrixRowType::ROW_0)), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_0).cross(N.getWorld().get(MatrixRowType::ROW_1)), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_0).cross(N.getWorld().get(MatrixRowType::ROW_2)), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_1).cross(N.getWorld().get(MatrixRowType::ROW_0)), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_1).cross(N.getWorld().get(MatrixRowType::ROW_1)), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_1).cross(N.getWorld().get(MatrixRowType::ROW_2)), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_2).cross(N.getWorld().get(MatrixRowType::ROW_0)), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_2).cross(N.getWorld().get(MatrixRowType::ROW_1)), M, N)&&
	OBBOverlap(M.getWorld().get(MatrixRowType::ROW_2).cross(N.getWorld().get(MatrixRowType::ROW_2)), M, N);
}

bool FlimMath::OBBOverlap(const Vect & v, const CollisionVolumeOBB & M, const CollisionVolumeOBB & N)
{
	if (v.magSqr() > FLT_EPSILON)
	{
		//assert(!v.W());
		// compute M's max projection on v
		float projMax_M = MaxOBBProjectionLength(v, M);
		// compute N's max projection on v
		float projMax_N = MaxOBBProjectionLength(v, N);
		// D = abs((N's center - M's center).dot(v))

		Vect dist = (N.getCenter() - M.getCenter());
		dist.set(dist.X(), dist.Y(), dist.Z(), 0.0f);

		float D = abs(dist.dot(v)) / v.mag();
		// if D > Proj1 + Proj2, return false
		return (D <= projMax_M + projMax_N);
	}

	return true;
}

bool FlimMath::OBBOverlap(const Vect & v, const CollisionVolumeAABB & M, const CollisionVolumeOBB & N)
{
	if (v.magSqr() > FLT_EPSILON)
	{
		//assert(!v.W());
		// compute M's max projection on v
		float projMax_M = MaxOBBProjectionLength(v, M);
		// compute N's max projection on v
		float projMax_N = MaxOBBProjectionLength(v, N);
		// D = abs((N's center - M's center).dot(v))

		Vect dist = (N.getCenter() - M.getCenter());
		dist.set(dist.X(), dist.Y(), dist.Z(), 0.0f);

		float D = abs(dist.dot(v)) / v.mag();
		// if D > Proj1 + Proj2, return false
		return (D <= projMax_M + projMax_N);
	}

	return true;
}

float FlimMath::MaxOBBProjectionLength(const Vect & v, const CollisionVolumeOBB & obb)
{
	// move v to local space --> multiply by inverse world
	Vect v_prime = v * obb.getWorld().getInv();

	// compute max projection length: abs(v'x * halfDiagonal.x) + abs(v'y * halfDiagonal.y) + abs(v'z * halfDiagonal.z)
	float projMax = abs(v_prime.X() * obb.getHalfDiagonal().X()) + abs(v_prime.Y() * obb.getHalfDiagonal().Y()) + abs(v_prime.Z() * obb.getHalfDiagonal().Z());

	// scale: scaleSquare * (projMax / v.mag())
	return obb.getScaleSquared() * (projMax / v.mag());
}


float FlimMath::MaxOBBProjectionLength(const Vect & v, const CollisionVolumeAABB & obb)
{
	// move v to local space --> multiply by inverse world
	Vect v_prime = v * obb.getWorld().getInv();

	// compute max projection length: abs(v'x * halfDiagonal.x) + abs(v'y * halfDiagonal.y) + abs(v'z * halfDiagonal.z)
	float projMax = abs(v_prime.X() * obb.getHalfDiagonal().X()) + abs(v_prime.Y() * obb.getHalfDiagonal().Y()) + abs(v_prime.Z() * obb.getHalfDiagonal().Z());

	// scale: scaleSquare * (projMax / v.mag())
	return obb.getScaleSquared() * (projMax / v.mag());
}


bool FlimMath::Intersect(const CollisionVolumeAABB & A, const CollisionVolumeAABB & B)
{

	//test all three axes 
	return FlimMath::Overlap(A.getMin().X(), A.getMax().X(), B.getMin().X(), B.getMax().X()) &&
		   FlimMath::Overlap(A.getMin().Y(), A.getMax().Y(), B.getMin().Y(), B.getMax().Y()) &&
		   FlimMath::Overlap(A.getMin().Z(), A.getMax().Z(), B.getMin().Z(), B.getMax().Z());
}

bool FlimMath::Intersect(const CollisionVolumeOcclusionLine & line, const CollisionVolumeBSphere & bs)
{
	float num = Vect(line.getEndPoint() - line.getStartPoint()).cross(line.getStartPoint() - bs.getCenter()).magSqr();
	float denom = Vect(line.getEndPoint() - line.getStartPoint()).magSqr();

	float d = num / denom;

	return d < (bs.getRadius() * bs.getRadius());
}

bool FlimMath::Intersect(const CollisionVolumeOcclusionLine & , const CollisionVolumeOBB & )
{
	return false;
}

bool FlimMath::Intersect(const CollisionVolumeOcclusionLine & , const CollisionVolumeAABB &)
{
	return false;
}

bool FlimMath::Intersect(const CollisionVolumeOcclusionLine & , const CollisionVolumeOcclusionLine & )
{
	return false;
}

bool FlimMath::Intersect(Collidable * A, Collidable * B)
{
	return A->GetCollisionVolume().Intersect(B->GetCollisionVolume()); // double dispatch
}

bool FlimMath::Intersect(const CollisionVolume& A, const CollisionVolumeAABB& B)
{
	return A.Intersect(B);
}

const Vect FlimMath::getMin(Vect * points, int size)
{
	assert(points);
	float minX = points->X();
	float minY = points->Y();
	float minZ = points->Z();

	int i = 0;
	while (i < size)
	{
		if (points[i].X() < minX)
		{
			minX = points[i].X();
		}

		if (points[i].Z() < minZ)
		{
			minZ = points[i].Z();
		}

		if (points[i].Y() < minY)
		{
			minY = points[i].Y();
		}

		i++;
	}

	return Vect(minX, minY, minZ);
}

const Vect FlimMath::getMax(Vect * points, int size)
{
	assert(points);
	float maxX = 0.0f;
	float maxY = 0.0f;
	float maxZ = 0.0f;

	int i = 0;
	while (i < size)
	{
		if (points[i].X() > maxX)
		{
			maxX = points[i].X();
		}

		if (points[i].Z() > maxZ)
		{
			maxZ = points[i].Z();
		}

		if (points[i].Y() > maxY)
		{
			maxY = points[i].Y();
		}

		i++;
	}

	return Vect(maxX, maxY, maxZ);
}



float FlimMath::ClampFloat(float clamp, float a, float b)
{
	if (clamp < a)
	{
		return a;
	}
	else if (b < clamp)
	{
		return b;
	}
	else
	{
		return clamp;
	}
}




bool FlimMath::Overlap(float aMin, float aMax, float bMin, float bMax)
{
	if (aMax < bMin || bMax < aMin)
	{
		return false;
	}
	else
	{
		return true;
	}
}


const errcode FlimMath::getMinComponent(Vect & worldVector, float & minX, float & minY, float & minZ)
{
	if (worldVector.X() < minX)
	{
		minX = worldVector.X();
	}
	  
	if (worldVector.Z() < minZ)
	{
		minZ = worldVector.Z();
	}

	if (worldVector.Y() < minY)
	{
		minY = worldVector.Y();
	}
	return errcode::success;
}

const errcode FlimMath::getMaxComponent(Vect & worldVector, float & maxX, float & maxY, float & maxZ)
{
	if (worldVector.X() > maxX)
	{
		maxX = worldVector.X();
	}

	if (worldVector.Z() > maxZ)
	{
		maxZ = worldVector.Z();
	}

	if (worldVector.Y() > maxY)
	{
		maxY = worldVector.Y();
	}
	return errcode::success;
}

const errcode FlimMath::getMaxComponent(Vect & globalMax, Vect& localMax)
{
	if (localMax.X() > globalMax.X())
	{
		globalMax.set(localMax.X(), globalMax.Y(), globalMax.Z());
	}

	if (localMax.Y() > globalMax.Y())
	{
		globalMax.set(globalMax.X(), localMax.Y(), globalMax.Z());
	}

	if (localMax.Z() > globalMax.Z())
	{
		globalMax.set(globalMax.X(), globalMax.Y(), localMax.Z());
	}
	return errcode::success;
}

const errcode FlimMath::getMinComponent(Vect & globalMin, Vect& localMin)
{
	if (localMin.X() < globalMin.X())
	{
		globalMin.set(localMin.X(), globalMin.Y(), globalMin.Z());
	}

	if (localMin.Y() < globalMin.Y())
	{
		globalMin.set(globalMin.X(), localMin.Y(), globalMin.Z());
	}

	if (localMin.Z() < globalMin.Z())
	{
		globalMin.set(globalMin.X(), globalMin.Y(), localMin.Z());
	}
	return errcode::success;
}

bool FlimMath::DifferentEnough(const Vect & v1, const Vect & v2, float epsilon)
{
	Vect diff = v1 - v2;
	return (diff.X() > epsilon) || (diff.Y() > epsilon) || (diff.Z() > epsilon);
}

const Vect FlimMath::getMin(Vect * points, int size, Matrix& world)
{
	assert(points);
	Vect worldVector = points[0] * world;
	float minX = worldVector.X();
	float minY = worldVector.Y();
	float minZ = worldVector.Z();

	int i = 0;
	while (i < size)
	{
		worldVector = points[i] * world;
		getMinComponent(worldVector, minX, minY, minZ);

		i++;
	}

	return Vect(minX, minY, minZ);
}

const Vect FlimMath::getMax(Vect * points, int size, Matrix& world)
{
	assert(points);
	Vect worldVector = points[0] * world;
	float maxX = worldVector.X();
	float maxY = worldVector.Y();
	float maxZ = worldVector.Z();

	int i = 0;
	while (i < size)
	{
		worldVector = points[i] * world;
		getMaxComponent(worldVector, maxX, maxY, maxZ);

		i++;
	}

	return Vect(maxX, maxY, maxZ);
}