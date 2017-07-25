#include "CollisionManager.h"

errcode CollisionManager::ProcessCollisionTests()
{
	errcode err = errcode::success;
	std::list<CollisionTestCommand*>::iterator iter = this->collisionTestCmds.begin();
	while (iter != collisionTestCmds.end())
	{
		if ((*iter))
		{
			(*iter)->execute();
			iter++;
		}
		else
		{
			assert(false);
			err = errcode::failure;
		}
	}

	return err;
}

errcode CollisionManager::UpdateGroupCollisionVolumes()
{
	errcode err = errcode::success;
	std::list<CollisionUpdateCommand*>::iterator iter = this->updateCmds.begin();
	while (iter != updateCmds.end())
	{
		if ((*iter))
		{
			(*iter)->execute();
			iter++;
		}
		else
		{
			assert(false);
			err = errcode::failure;
		}
	}

	return err;
}

errcode CollisionManager::Update()
{
	UpdateGroupCollisionVolumes();
	this->ProcessCollisionTests();

	return errcode::success;
}

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{
	// clean up test commands, call delete commands, clean up delete commands
	std::list<CollisionTestCommand*>::iterator iter = this->collisionTestCmds.begin();
	while (iter != collisionTestCmds.end())
	{
		if ((*iter))
		{
			delete (*iter);
			(*iter) = nullptr;
			iter++;
		}
		else
		{
			assert(false);
		}
	}
	collisionTestCmds.clear();

	// clean up test commands, call delete commands, clean up delete commands
	std::list<CollidableGroupDeleteCmd*>::iterator deleteIter = this->deleteCmds.begin();
	while (deleteIter != deleteCmds.end())
	{
		if ((*deleteIter))
		{
			(*deleteIter)->execute();
			delete (*deleteIter);
			(*deleteIter) = nullptr;
			deleteIter++;
		}
		else
		{
			assert(false);
		}
	}
	deleteCmds.clear();

	//DebugMsg::out("collision manager cleaned\n");

}

errcode CollisionManager::AddDeleteCommand(CollidableGroupDeleteCmd * cmd)
{
	errcode err = errcode::success;
	if (cmd)
	{
		this->deleteCmds.push_front(cmd);
	}
	else
	{
		assert(false);
		err = errcode::failure;
	}
	return errcode::success;
}
