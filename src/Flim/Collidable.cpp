#include "Collidable.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"
#include "CollisionDeregistrationCommand.h"



Collidable::Collidable()
{
	regState = RegistrationState::DEREG;
	regCommand = nullptr;
	deregCommand = nullptr;
	collVolume = nullptr;
	defaultBS = nullptr;
	colliding = false;
}

Collidable::~Collidable()
{
	if (collVolume)
	{
		delete collVolume;
	}
	if (regCommand)
	{
		delete regCommand;
		regCommand = nullptr;
	}
	if (deregCommand)
	{
		delete deregCommand;
		deregCommand = nullptr;
	}
	//DebugMsg::out("Collidable cleaned\n");
}

const CollisionVolume & Collidable::GetCollisionVolume() const
{
	return *this->collVolume;
}

errcode Collidable::SetColliderModel(Model * mod, CollisionVolumeType vol)
{
	errcode err = errcode::success;
	if (collVolume) // avoid leaks
	{
		delete collVolume;
		collVolume = nullptr;
	}

	if (!defaultBS)
	{
		defaultBS = new CollisionVolumeBSphere();
	}

	switch (vol)
	{
		case CollisionVolumeType::BSPHERE:
		{
			this->collVolume = new CollisionVolumeBSphere();
			break;
		}
		case CollisionVolumeType::AABB:
		{
			this->collVolume = new CollisionVolumeAABB();
			break;
		}
		case CollisionVolumeType::OBB:
		{
			this->collVolume = new CollisionVolumeOBB(mod);
			break;
		}
		case CollisionVolumeType::OCCLUSION_LINE:
		{
			this->collVolume = new CollisionVolumeOcclusionLine();
			break;
		}
		default:
			assert(false);
			return errcode::failure;
	}
	if (mod)
	{
		this->pColModel = mod;
	}
	else
	{
		err = errcode::failure;
	}
	return err;
}

errcode Collidable::UpdateCollisionData(Matrix & mat)
{
	if (!(defaultBS && collVolume))
	{
		return errcode::failure;
	}
	this->collVolume->ComputeData(this->pColModel, mat);
	this->defaultBS->ComputeData(this->pColModel, mat);
	//Visualizer::ShowBSphere(*defaultBS);

	return errcode::success;
}

std::list<Collidable*>::iterator Collidable::GetDeletionIter()
{
	return deleteIter;
}

errcode Collidable::SetDeletionIter(std::list<Collidable*>::iterator in)
{
	deleteIter = in;
	return errcode::success;
}

