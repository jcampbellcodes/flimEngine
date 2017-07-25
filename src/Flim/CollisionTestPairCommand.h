#pragma once
#ifndef COLLISIONTESTPairCMD_H
#define COLLISIONTESTPairCMD_H

#include "CollisionTestCommand.h"
#include "CollidableGroup.h"
#include "MathTools.h"
#include "FlimColor.h"
#include "Visualizer.h"
template <typename C1, typename C2>
class CollisionTestPairCommand : public CollisionTestCommand
{
public:
	CollisionTestPairCommand()
		: Collection1(CollidableGroup<C1>::GetCollection()),
		Collection2(CollidableGroup<C2>::GetCollection())
	{
	};

	~CollisionTestPairCommand()
	{
		//DebugMsg::out("collision test pair command cleaned\n");
	}

	virtual void execute() override
	{
		Collection1 = CollidableGroup<C1>::GetCollection();
		Collection2 = CollidableGroup<C2>::GetCollection();

		// FOUR STEPS

		// 1 test BIG aabbs; early out if false
		if (!FlimMath::Intersect(CollidableGroup<C1>::getAABB(), CollidableGroup<C2>::getAABB()))
		{

			Visualizer::ShowAABB(CollidableGroup<C1>::getAABB(), flimColor::green);
			Visualizer::ShowAABB(CollidableGroup<C2>::getAABB(), flimColor::green);


			return; // early out
		}
		else // in the zone!
		{
			Visualizer::ShowAABB(CollidableGroup<C1>::getAABB(), flimColor::red);
			Visualizer::ShowAABB(CollidableGroup<C2>::getAABB(), flimColor::pink);
		}



		


		// 2 test everyone in Collection 1 against C2 BIG aabb... everyone who collides, add to testlist
		
		std::list<C1*> innerCollided;
		std::set<C1*>::iterator it1 = Collection1.begin();
		
		while (it1 != Collection1.end())
		{
			//Visualizer::ShowBSphere((*it1)->getBSphere());
			if (FlimMath::Intersect((*it1)->getBSphere(), CollidableGroup<C2>::getAABB()))
			{
				innerCollided.push_back(*it1);		
				// 3 test *it1 against everyone in C2
				std::set<C2*>::iterator it2 = Collection2.begin();
				while (it2 != Collection2.end())
				{
					// 4 early out built into if statement
					if (FlimMath::Intersect((*it1)->getBSphere(), (*it2)->getBSphere()) && FlimMath::Intersect(*it1, *it2))
					{


						if (!(*it1)->getColliding())
						{
							(*it1)->CollisionEnter(*it2);
						}

						(*it1)->setColliding(true);

						if (!(*it2)->getColliding())
						{
							(*it2)->CollisionEnter(*it1);
						}

						(*it2)->setColliding(true);


						(*it1)->Collision(*it2);
						(*it2)->Collision(*it1);

						Visualizer::ShowCollisionVolume(*(*it1), flimColor::pink);
						Visualizer::ShowCollisionVolume(*(*it2), flimColor::red);
					}
					else
					{
						// check for past collisions
						std::set<C1*>::iterator nonCollIter1 = Collection1.begin();
						std::set<C2*>::iterator nonCollIter2 = Collection2.begin();

						while (nonCollIter1 != Collection1.end())
						{
							if ((*nonCollIter1)->getColliding())
							{
								(*nonCollIter1)->CollisionExit();
							}

							(*nonCollIter1)->setColliding(false);

							nonCollIter1++;
						}


						while (nonCollIter2 != Collection2.end())
						{

							if ((*nonCollIter2)->getColliding())
							{
								(*nonCollIter2)->CollisionExit();
							}

							(*nonCollIter2)->setColliding(false);

							nonCollIter2++;
						}
						Visualizer::ShowCollisionVolume(*(*it1), flimColor::blue);
						Visualizer::ShowCollisionVolume(*(*it2), flimColor::green);
					}


					it2++;
				}
			}
			
			++it1;
		}
		
	}

private:
	std::set<C1*> Collection1;
	std::set<C2*> Collection2;

};

#endif