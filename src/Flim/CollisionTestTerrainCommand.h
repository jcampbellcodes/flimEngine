#pragma once
#ifndef CollisionTestTerrainCMD_H
#define CollisionTestTerrainCMD_H

#include "CollisionTestCommand.h"
#include "CollidableGroup.h"
#include "MathTools.h"
#include "FlimColor.h"
#include "Visualizer.h"
#include "TerrainCellRange.h"

#include "SceneManager.h"

template <typename C>
class CollisionTestTerrainCommand : public CollisionTestCommand
{
public:
	CollisionTestTerrainCommand()
		: Collection(CollidableGroup<C>::GetCollection())
	{
	};

	~CollisionTestTerrainCommand()
	{
		//DebugMsg::out("collision test pair command cleaned\n");
	}

	virtual void execute() override
	{
		Collection = CollidableGroup<C>::GetCollection();
		FlimTerrain* terrain = SceneManager::getTerrain();
		if (!terrain)
		{
			return;
		}
		
		// get candidate cell's based on each bsphere in the collection
		for (auto it1 = Collection.begin(); it1 != Collection.end(); ++it1)
		{
			TerrainCellRange candidateCells(terrain, (*it1)->getBSphere());
			for (TerrainCellIter itCell = candidateCells.begin(); itCell != candidateCells.end(); ++itCell)
			{
				// check first the aabb against default bsphere
				if (FlimMath::Intersect((*it1)->getBSphere(), (*itCell).getAABB()))
				{
					// check now with the actual collidable
					
					if (FlimMath::Intersect((*it1)->GetCollisionVolume(), (*itCell).getAABB()))
					{
						// then they are colliding!

						(*it1)->CollisionTerrain((*itCell).getAABB());
						 


						Visualizer::ShowCollisionVolume(*(*it1), flimColor::red);
						Visualizer::ShowAABB((*itCell).getAABB(), flimColor::red);
						Visualizer::ShowBSphere((*it1)->getBSphere(), flimColor::red);
						return;
					}
					else
					{
						//Visualizer::ShowAABB((*itCell).getAABB(), flimColor::green);
						//Visualizer::ShowCollisionVolume(*(*it1), flimColor::green);
					}
					
					//Visualizer::ShowBSphere((*it1)->getBSphere(), flimColor::red);

				}
				else
				{
					//Visualizer::ShowBSphere((*it1)->getBSphere(), flimColor::green);
				}

			}

		}

	}

private:
	std::set<C*> Collection;

};

#endif