#pragma once
#ifndef COLLISIONDEREGCOMMAND_H
#define COLLISIONDEREGCOMMAND_H

#include "SceneDeregistrationCommand.h"
#include "CollidableGroup.h"

template <typename C>
class CollisionDeregistrationCommand : public SceneDeregistrationCommand
{
public:
	CollisionDeregistrationCommand(C* c) : collidable(c) 
	{
		DebugMsg::out("collision deregistration command cleaned\n");
	}
	virtual void execute() override;

	virtual ~CollisionDeregistrationCommand()
	{
		DebugMsg::out("collision deregistration command cleaned\n");
	}

private:
	C* collidable;

};


template<typename C>
inline void CollisionDeregistrationCommand<C>::execute()
{
	assert(collidable->Collidable::regState == RegistrationState::DEREG_PENDING);
	CollidableGroup<C>::Deregister(collidable);
	collidable->Collidable::regState = RegistrationState::DEREG;

}


#endif
