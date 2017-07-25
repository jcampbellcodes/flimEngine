#pragma once
#ifndef COLLISIONUPDATECMD_H
#define COLLISIONUPDATECMD_H

#include "CollisionUpdateCommand.h"
#include "CollidableGroup.h"

template <typename C>
class CollidableGroupUpdateCommand : public CollisionUpdateCommand
{
public:
	CollidableGroupUpdateCommand()
		: Collection(CollidableGroup<C>::GetCollection())
	{
	};

	~CollidableGroupUpdateCommand()
	{
		//DebugMsg::out("collision test self command cleaned\n");
	}

	virtual void execute() override
	{
		Collection = CollidableGroup<C>::GetCollection();

		if (!Collection.size())
		{
			return;
		}

		// 2d for-loop
		std::set<C*>::iterator it1 = Collection.begin();

		CollisionVolumeBSphere bs;
		Vect maxBS;
		Vect minBS;

		bs = (*it1)->getBSphere();
		Vect minAABB(bs.getCenter());
		Vect maxAABB(bs.getCenter());

		while (it1 != Collection.end())
		{
			// compute AABB from bsphere
			
			// center - radius on all axes is min max for all bspheres -- subtract for min, add for max
			bs = (*it1)->getBSphere();
			maxBS = Vect(bs.getCenter().X() + bs.getRadius(), bs.getCenter().Y() + bs.getRadius(), bs.getCenter().Z() + bs.getRadius());
			minBS = Vect(bs.getCenter().X() - bs.getRadius(), bs.getCenter().Y() - bs.getRadius(), bs.getCenter().Z() - bs.getRadius());
			
			// get min, get max
			// test vs overall min/max
			FlimMath::getMaxComponent(maxAABB, maxBS);
			FlimMath::getMinComponent(minAABB, minBS);

			++it1;
		}

		// use min/max to set collidable group's AABB
		CollidableGroup<C>::setAABB(minAABB, maxAABB);

	}

private:
	std::set<C*> Collection;

};

#endif