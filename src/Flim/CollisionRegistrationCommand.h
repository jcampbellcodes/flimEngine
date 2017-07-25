#pragma once
#ifndef COLLISIONREGCOMMAND_H
#define COLLISIONREGCOMMAND_H

#include "SceneRegistration.h"
#include "CollidableGroup.h"
#include "Collidable.h"

template <typename C>
class CollisionRegistrationCommand : public SceneRegistrationCommand
{
public:
	CollisionRegistrationCommand(C* c) : collidable(c)
	{

	}

	CollisionRegistrationCommand() = delete;
	CollisionRegistrationCommand(const CollisionRegistrationCommand&)
	{
		assert(false);
	}
	CollisionRegistrationCommand& operator=(const CollisionRegistrationCommand&) = delete;



	~CollisionRegistrationCommand()
	{
		DebugMsg::out("collision registration command cleaned\n");
	}

	virtual void execute() override;


private:
	C* collidable;

};


template<typename C>
inline void CollisionRegistrationCommand<C>::execute()
{

	assert(collidable->Collidable::regState == RegistrationState::REG_PENDING);
	CollidableGroup<C>::Register(collidable);
	collidable->Collidable::regState = RegistrationState::REG;

}


#endif
