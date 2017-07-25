#pragma once
#ifndef COLLISIONVOLUME_H
#define COLLISIONVOLUME_H

#include "AzulCore.h"
#include "err.h"
#include "Align16.h"
//#include "CollisionVolumeBSphere.h"
//#include "CollisionVolumeAABB.h"

class Model; // may need to define?
class Matrix;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeOcclusionLine;

class CollisionVolume : public Align16
{
public:
	// big four
	CollisionVolume() = default;
	virtual ~CollisionVolume()
	{
		//DebugMsg::out("Collision volume destroyed\n");
	}
	CollisionVolume(const CollisionVolume&) = default;
	CollisionVolume& operator= (const CollisionVolume&) = default;

	//methods

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode CollisionVolume::ComputeData(Model* mod, Matrix& mat) = 0;
	///
	/// \brief	Calculates the collision data based on a model and its world matrix.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	mod	If non-null, the modifier.
	/// \param [in,out]	mat	The matrix.
	///
	/// \return	The calculated data.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode ComputeData(Model* mod, Matrix& mat) = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual bool CollisionVolume::Intersect(const CollisionVolume& other) = 0;
	///
	/// \brief	Test intersection with a collision volume.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param	other	Collision volume to test intersection with.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual bool Intersect(const CollisionVolume& other) const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual bool CollisionVolume::Intersect(const CollisionVolumeBSphere& other) = 0;
	///
	/// \brief	Test intersection with another Bsphere.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param	other	Bsphere to test collision with.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual bool Intersect(const CollisionVolumeBSphere& other) const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual bool CollisionVolume::Intersect(const CollisionVolumeAABB& other) = 0;
	///
	/// \brief	Intersects the given other.
	///
	/// \author	Jack Campbell
	/// \date	4/7/2017
	///
	/// \param	other	The other.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual bool Intersect(const CollisionVolumeAABB& other) const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual bool CollisionVolume::Intersect(const CollisionVolumeOBB& other) const = 0;
	///
	/// \brief	Intersects the given other.
	///
	/// \author	Jack Campbell
	/// \date	4/15/2017
	///
	/// \param	other	The other.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual bool Intersect(const CollisionVolumeOBB& other) const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual bool CollisionVolume::Intersect(const CollisionVolumeOcclusionLine&) const = 0;
	///
	/// \brief	Intersects the given parameter 1.
	///
	/// \author	Jack Campbell
	/// \date	5/3/2017
	///
	/// \param	parameter1	The first parameter.
	///
	/// \return	True if it succeeds, false if it fails.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual bool Intersect(const CollisionVolumeOcclusionLine&) const = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode CollisionVolume::DebugView(const Collidable* col) = 0;
	///
	/// \brief	Debug view.
	///
	/// \author	Jack Campbell
	/// \date	4/7/2017
	///
	/// \param	col	The col.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode DebugView(const Vect& col) const = 0;

};

#endif