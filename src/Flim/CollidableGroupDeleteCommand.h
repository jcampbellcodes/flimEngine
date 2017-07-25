#pragma once
#ifndef COLLISIONDELETEREGCOMMAND_H
#define COLLISIONDELETEREGCOMMAND_H

#include "CollidableGroup.h"
#include "CollidableGroupDelete.h"

template <typename C>
class CollidableGroupDeleteCommand : public CollidableGroupDeleteCmd
{
public:
	CollidableGroupDeleteCommand(){}
	~CollidableGroupDeleteCommand()
	{
		//DebugMsg::out("collidable group delete command cleaned\n");
	}
	void execute() override;

};


template<typename C>
inline void CollidableGroupDeleteCommand<C>::execute()
{
	CollidableGroup<C>::Terminate();
}


#endif
