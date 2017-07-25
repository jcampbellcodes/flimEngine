#pragma once
#ifndef MATHTOOLS_H
#define MATHTOOLS_H

//class CollisionVolumeBSphere;
//class CollisionVolumeAABB;
//class CollisonVolume;
//class Collidable;

#include "CollisionVolumeBSphere.h"
#include "CollisionVolume.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionVolumeOcclusionLine.h"
//#include "Collidable.h"
class Collidable;
class Vect;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	FlimMath
///
/// \brief	A flim mathematics.
/// \ingroup TOOLS
///
/// \author	Jack Campbell
/// \date	3/13/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class FlimMath
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);
	///
	/// \brief	Intersection math for two bspheres.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \param	A	The CollisionVolumeBSphere to process.
	/// \param	B	The CollisionVolumeBSphere to process.
	/// 			
	/// 			
	/// \code
	/// 	 
	/// 	 // Testing two collidables
	/// 	 bool test_result = FlimMath::Intersect(Ship1->GetBSphere(), Ship2->GetBSphere());
	/// 	 
	/// \endcode
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	// bsphere bsphere

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeBSphere to process.
	/// \param	B	The CollisionVolumeBSphere to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeBSphere& B);
	// bsphere point

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeBSphere& A, const Vect& P);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeBSphere to process.
	/// \param	P	The Vect to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeBSphere& A, const Vect& P);
	// bsphere aabb

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeAABB& B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeBSphere to process.
	/// \param	B	The CollisionVolumeAABB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeAABB& B);
	// bsphere obb

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeBSphere to process.
	/// \param	B	The CollisionVolumeOBB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeBSphere& A, const CollisionVolumeOBB& B);
	// aabb obb

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeAABB to process.
	/// \param	B	The CollisionVolumeOBB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeAABB& A, const CollisionVolumeOBB& B);
	// obb obb

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeOBB to process.
	/// \param	B	The CollisionVolumeOBB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeOBB& A, const CollisionVolumeOBB& B);
	// aabb aabb

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeAABB & A, const CollisionVolumeAABB & B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeAABB to process.
	/// \param	B	The CollisionVolumeAABB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeAABB & A, const CollisionVolumeAABB & B);
	// line bsphere

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeOcclusionLine& A, const CollisionVolumeBSphere& B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeOcclusionLine to process.
	/// \param	B	The CollisionVolumeBSphere to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeOcclusionLine& A, const CollisionVolumeBSphere& B);
	// line obb

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeOcclusionLine& A, const CollisionVolumeOBB& B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeOcclusionLine to process.
	/// \param	B	The CollisionVolumeOBB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeOcclusionLine& A, const CollisionVolumeOBB& B);
	//line aabb

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeOcclusionLine & A, const CollisionVolumeAABB & B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeOcclusionLine to process.
	/// \param	B	The CollisionVolumeAABB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeOcclusionLine & A, const CollisionVolumeAABB & B);
	// line line
	// ///

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolumeOcclusionLine & A, const CollisionVolumeOcclusionLine & B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolumeOcclusionLine to process.
	/// \param	B	The CollisionVolumeOcclusionLine to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolumeOcclusionLine & A, const CollisionVolumeOcclusionLine & B);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(Collidable* A, Collidable* B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	A	If non-null, the Collidable to process.
	/// \param [in,out]	B	If non-null, the Collidable to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(Collidable* A, Collidable* B);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Intersect(const CollisionVolume & A, const CollisionVolumeAABB & B);
	///
	/// \brief	Intersects.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	A	The CollisionVolume to process.
	/// \param	B	The CollisionVolumeAABB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Intersect(const CollisionVolume & A, const CollisionVolumeAABB & B);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const Vect FlimMath::getMin(Vect*, int);
	///
	/// \brief	Finds the min of the given arguments.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	parameter1	If non-null, the first parameter.
	/// \param 		   	parameter2	The second parameter.
	///
	/// \return	The calculated minimum.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const Vect getMin(Vect*, int);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const Vect FlimMath::getMax(Vect*, int);
	///
	/// \brief	Finds the max of the given arguments.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	parameter1	If non-null, the first parameter.
	/// \param 		   	parameter2	The second parameter.
	///
	/// \return	The calculated maximum.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const Vect getMax(Vect*, int);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const errcode FlimMath::getMinComponent(Vect& vector, float& x, float& y, float& z);
	///
	/// \brief	Gets minimum component.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	vector	The vector.
	/// \param [in,out]	x	  	The float to process.
	/// \param [in,out]	y	  	The float to process.
	/// \param [in,out]	z	  	The float to process.
	///
	/// \return	The minimum component.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const errcode getMinComponent(Vect& vector, float& x, float& y, float& z);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const errcode FlimMath::getMaxComponent(Vect& vector, float& x, float& y, float& z);
	///
	/// \brief	Gets maximum component.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	vector	The vector.
	/// \param [in,out]	x	  	The float to process.
	/// \param [in,out]	y	  	The float to process.
	/// \param [in,out]	z	  	The float to process.
	///
	/// \return	The maximum component.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const errcode getMaxComponent(Vect& vector, float& x, float& y, float& z);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const errcode FlimMath::getMaxComponent(Vect & globalMax, Vect & localMax);
	///
	/// \brief	Gets maximum component.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	globalMax	The global maximum.
	/// \param [in,out]	localMax 	The local maximum.
	///
	/// \return	The maximum component.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const errcode getMaxComponent(Vect & globalMax, Vect & localMax);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const errcode FlimMath::getMinComponent(Vect & globalMin, Vect & localMin);
	///
	/// \brief	Gets minimum component.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	globalMin	The global minimum.
	/// \param [in,out]	localMin 	The local minimum.
	///
	/// \return	The minimum component.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const errcode getMinComponent(Vect & globalMin, Vect & localMin);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::DifferentEnough(const Vect& v1, const Vect& v2, float epsilon);
	///
	/// \brief	Different enough.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	v1	   	The first Vect.
	/// \param	v2	   	The second Vect.
	/// \param	epsilon	The epsilon.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool DifferentEnough(const Vect& v1, const Vect& v2, float epsilon);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static float FlimMath::ClampFloat(float clamp, float a, float b);
	///
	/// \brief	Clamp float.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	clamp	The clamp.
	/// \param	a	 	The float to process.
	/// \param	b	 	The float to process.
	///
	/// \return	A float.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static float ClampFloat(float clamp, float a, float b);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Vect FlimMath::ClampPoint(Vect& point, const Vect& min, const Vect& max);
	///
	/// \brief	Clamp point.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	point	The point.
	/// \param 		   	min  	The minimum.
	/// \param 		   	max  	The maximum.
	///
	/// \return	A Vect.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Vect ClampPoint(Vect& point, const Vect& min, const Vect& max);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::OBBOverlap(const Vect& v, const CollisionVolumeOBB& M, const CollisionVolumeOBB& N);
	///
	/// \brief	Obb overlap.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	v	The Vect to process.
	/// \param	M	The CollisionVolumeOBB to process.
	/// \param	N	The CollisionVolumeOBB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool OBBOverlap(const Vect& v, const CollisionVolumeOBB& M, const CollisionVolumeOBB& N);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::OBBOverlap(const Vect& v, const CollisionVolumeAABB& M, const CollisionVolumeOBB& N);
	///
	/// \brief	Obb overlap.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	v	The Vect to process.
	/// \param	M	The CollisionVolumeAABB to process.
	/// \param	N	The CollisionVolumeOBB to process.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool OBBOverlap(const Vect& v, const CollisionVolumeAABB& M, const CollisionVolumeOBB& N);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static bool FlimMath::Overlap(float aMin, float aMax, float bMin, float bMax);
	///
	/// \brief	Overlaps.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	aMin	The minimum.
	/// \param	aMax	The maximum.
	/// \param	bMin	The minimum.
	/// \param	bMax	The maximum.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool Overlap(float aMin, float aMax, float bMin, float bMax);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static float FlimMath::MaxOBBProjectionLength(const Vect& v, const CollisionVolumeOBB& obb);
	///
	/// \brief	Maximum obb projection length.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	v  	The Vect to process.
	/// \param	obb	The obb.
	///
	/// \return	A float.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static float MaxOBBProjectionLength(const Vect& v, const CollisionVolumeOBB& obb);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static float FlimMath::MaxOBBProjectionLength(const Vect& v, const CollisionVolumeAABB& obb);
	///
	/// \brief	Maximum obb projection length.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	v  	The Vect to process.
	/// \param	obb	The obb.
	///
	/// \return	A float.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static float MaxOBBProjectionLength(const Vect& v, const CollisionVolumeAABB& obb);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const Vect FlimMath::getMin(Vect*, int, Matrix&);
	///
	/// \brief	Finds the min of the given arguments.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	parameter1	If non-null, the first parameter.
	/// \param 		   	parameter2	The second parameter.
	/// \param [in,out]	parameter3	The third parameter.
	///
	/// \return	The calculated minimum.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const Vect getMin(Vect*, int, Matrix&);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const Vect FlimMath::getMax(Vect*, int, Matrix&);
	///
	/// \brief	Finds the max of the given arguments.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	parameter1	If non-null, the first parameter.
	/// \param 		   	parameter2	The second parameter.
	/// \param [in,out]	parameter3	The third parameter.
	///
	/// \return	The calculated maximum.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const Vect getMax(Vect*, int, Matrix&);
};

#endif 