#pragma once
#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <list>
#include "CollisionTestCommand.h"
#include "CollisionTestPairCommand.h"
#include "CollisiontestSelfCommand.h"
#include "CollidableGroupDeleteCommand.h"
#include "CollidableGroupUpdateCommand.h"
#include "CollisionTestTerrainCommand.h"
#include "err.h"


class CollisionManager
{
private:
	std::list<CollisionTestCommand*> collisionTestCmds;
	std::list<CollisionUpdateCommand*> updateCmds;
	std::list<CollidableGroupDeleteCmd*> deleteCmds;

	friend class Scene;

	errcode ProcessCollisionTests();
	errcode UpdateGroupCollisionVolumes();
	errcode Update();

public:
	CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator= (const CollisionManager&) = delete;
	~CollisionManager();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	template <typename T1, typename T2> errcode CollisionManager::SetCollisionPair();
	///
	/// \brief	Registers collision for all gameobjects of the first type with gameobjects of the second type.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \ingroup COLLISIONREGISTRATION
	/// \tparam	T1	Collision type. (User defined, type of a gameobject)
	/// \tparam	T2	A different collision type. (User defined, type of a gameobject)
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename T1, typename T2>
	errcode SetCollisionPair();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	template <typename C> errcode CollisionManager::SetCollisionSelf();
	///
	/// \brief	Registers collision for gameobjects of their own type.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup COLLISIONREGISTRATION
	/// \tparam	C	Collision type.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename C>
	errcode SetCollisionSelf();


	template <typename C>
	errcode SetCollisionTerrain();
	

	errcode AddDeleteCommand(CollidableGroupDeleteCmd* cmd);

};


template <typename C1, typename C2>
inline errcode CollisionManager::SetCollisionPair()
{
	errcode err = errcode::success;

	CollisionTestPairCommand<C1, C2>* newCmd = new CollisionTestPairCommand<C1,C2>();

	CollidableGroupUpdateCommand<C1>* newUpdateCmd = new CollidableGroupUpdateCommand<C1>();
	assert(newUpdateCmd);
	updateCmds.push_front(newUpdateCmd);



	CollidableGroupUpdateCommand<C2>* newUpdateCmdSecond = new CollidableGroupUpdateCommand<C2>();
	assert(newUpdateCmdSecond);
	updateCmds.push_front(newUpdateCmdSecond);

	
	if (newCmd)
	{
		collisionTestCmds.push_front(newCmd);
	}
	else
	{
		err = errcode::failure;
	}

	return err;
}

template<typename C>
inline errcode CollisionManager::SetCollisionSelf()
{
	errcode err = errcode::success;

	CollisionTestSelfCommand<C>* newCmd = new CollisionTestSelfCommand<C>();
	CollidableGroupUpdateCommand<C>* newUpdateCmd = new CollidableGroupUpdateCommand<C>();
	assert(newUpdateCmd);

	updateCmds.push_front(newUpdateCmd);

	if (newCmd)
	{
		collisionTestCmds.push_front(newCmd);
	}
	else
	{
		err = errcode::failure;
	}

	return err;
}



template<typename C>
inline errcode CollisionManager::SetCollisionTerrain()
{
	errcode err = errcode::success;

	CollisionTestTerrainCommand<C>* newCmd = new CollisionTestTerrainCommand<C>();
	CollidableGroupUpdateCommand<C>* newUpdateCmd = new CollidableGroupUpdateCommand<C>();
	assert(newUpdateCmd);

	updateCmds.push_front(newUpdateCmd);

	if (newCmd)
	{
		collisionTestCmds.push_front(newCmd);
	}
	else
	{
		err = errcode::failure;
	}

	return err;
}


#endif

