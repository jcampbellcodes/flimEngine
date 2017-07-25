#pragma once
#ifndef COLLISIONTESTSELFCMD_H
#define COLLISIONTESTSELFCMD_H

#include "CollisionTestCommand.h"
#include "CollidableGroup.h"

template <typename C>
class CollisionTestSelfCommand : public CollisionTestCommand
{
public:
	CollisionTestSelfCommand()
		: Collection(CollidableGroup<C>::GetCollection())
	{
	};

	~CollisionTestSelfCommand()
	{
		//DebugMsg::out("collision test self command cleaned\n");
	}

	virtual void execute() override
	{
		Collection = CollidableGroup<C>::GetCollection();
		
		// 2d for-loop
		std::set<C*>::iterator it1 = Collection.begin();
		std::set<C*>::iterator it2 = it1;

		while (it1 != Collection.end())
		{
			// checks validity of next iterator, 
			// guarauntees it1 will not check against itself, 
			// and increments to iterate through the list
			while (++it2 != Collection.end())
			{

				if (FlimMath::Intersect((*it1)->getBSphere(), (*it2)->getBSphere()) && FlimMath::Intersect(*it1, *it2))
				{
					(*it1)->Collision(*it2);
					(*it2)->Collision(*it1);
					/*

					Submits a command to execute the renderBSphere method in the engine's draw

					*/

					Visualizer::ShowCollisionVolume(*(*it1), flimColor::red);
					Visualizer::ShowCollisionVolume(*(*it2), flimColor::red);

				}
				else
				{
					Visualizer::ShowCollisionVolume(*(*it1), flimColor::green);
					Visualizer::ShowCollisionVolume(*(*it2), flimColor::green);
				}
			}
			it2 = it1;
			it1++;
		}

	}

private:
	std::set<C*> Collection;

};

#endif