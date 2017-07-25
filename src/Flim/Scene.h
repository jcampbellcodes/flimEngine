#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "err.h"
#include "AzulCore.h"
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "KeyboardEventManager.h"

#include "CameraManager.h"

class Command;
class Executioner;
class Alarmable;
class Inputable;
class GameObject;
class SceneChangeCommand;
class SceneUpdateCommand;
class CollisionManager;
class FlimTerrain;

class Scene
{
private:
	CollisionManager* collisionManager;
	friend class SceneManager;
	friend class Updatable;
	friend class Drawable;
	friend class Collidable;
	template <typename C> friend class CollidableGroup;
	friend class Alarmable;
	friend class Inputable;
	friend class GameObject;
	friend class SceneChangeCommand;
	friend class SceneUpdateCommand;


	UpdatableManager* updateManager;
	DrawableManager* drawManager;
	AlarmableManager* alarmManager;
	KeyboardEventManager* keyboardManager;

	CameraManager* cameraManager;

	errcode Update();
	errcode Draw();
	friend class SceneManager;
	Executioner* executioner;
	FlimTerrain* terrain;


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Scene::Initialize() = 0;
	///
	/// \brief	Initializes this object.
	/// \ingroup SCENES
	/// \author	Jack Campbell
	/// \date	3/12/2017
	/// 		
	/// \par Virtual method for inherited scenes. Initialize all parts of your scene here.
	/// \code
	/// 	 
	/// 	 errcode SceneTest::Initialize()
	/// 	 {
	/// 		// make a new tank via a factory, set up the HUD, spawn enemies
	/// 	 }
	/// 	 
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode Initialize() = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	virtual errcode Scene::Terminate() = 0;
	///
	/// \brief	Gets the terminate.
	/// \ingroup SCENES
	/// \author	Jack Campbell
	/// \date	3/12/2017
	///
	/// \par Virtual callback for the ending of a scene. Clean up all the components of your scene.
	/// \code
	/// 	 
	/// 	 errcode SceneTest::Terminate()
	/// 	 {
	/// 		//scene has been ended. Return your tank to its factory, delete the HUD, make sure all enemies have been cleaned
	/// 	 }
	/// 	 
	/// 	 
	/// \endcode
	/// 
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual errcode Terminate() = 0;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Register(Updatable* in);
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Register(Updatable* in);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Deregister(Updatable* in);
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Deregister(Updatable* in);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Register(Drawable* in);
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Register(Drawable* in);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Deregister(Drawable* in);
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Deregister(Drawable* in); 

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Register(GameObject* in);
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Register(GameObject* in);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Deregister(GameObject* in);
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Deregister(GameObject* in);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Register(float t, Alarmable* in, AlarmableManager::ALARM_ID id);
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param 		   	t 	The float to process.
	/// \param [in,out]	in	If non-null, the in.
	/// \param 		   	id	The identifier.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Register(float t, Alarmable* in, AlarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Deregister(Alarmable* in, AlarmableManager::ALARM_ID id);
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	/// \param 		   	id	The identifier.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Deregister(Alarmable* in, AlarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Register(Inputable* in, AZUL_KEY key, input_type type);
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in  	If non-null, the in.
	/// \param 		   	key 	The key.
	/// \param 		   	type	The type.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Register(Inputable* in, AZUL_KEY key, input_type type);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::Deregister(Inputable* in, AZUL_KEY key, input_type type);
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in  	If non-null, the in.
	/// \param 		   	key 	The key.
	/// \param 		   	type	The type.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode Deregister(Inputable* in, AZUL_KEY key, input_type type);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void Scene::SubmitCommand(Command* in);
	///
	/// \brief	Submit command.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SubmitCommand(Command* in);

public:
	Scene();
	Scene(const Scene&) = default;
	virtual ~Scene();
	const Scene& operator=(const Scene&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	CameraManager* Scene::GetCamera()
	///
	/// \brief	Gets the camera.
	/// \ingroup CAMERA
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	Null if it fails, else the camera.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CameraManager* GetCamera() { return cameraManager; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode Scene::SetTerrain(const char* terrainName);
	///
	/// \brief	Sets a terrain.
	///\ingroup SCENES
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	terrainName	Name of the terrain.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode SetTerrain(const char* terrainName);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	FlimTerrain* Scene::GetTerrain() const
	///
	/// \brief	Gets the terrain.
	///\ingroup SCENES
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	Null if it fails, else the terrain.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	FlimTerrain* GetTerrain() const { return this->terrain; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	template <typename C1, typename C2> errcode Scene::SetCollisionPair();
	///
	/// \brief	Registers collision for two gameobject types with one another.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \ingroup SCENES
	/// \tparam	C1	First gameobject type
	/// \tparam	C2	Second gameobject type
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename C1, typename C2>
	errcode SetCollisionPair();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	template <typename C> errcode Scene::SetCollisionSelf();
	///
	/// \brief	Registers collision for a gameobject type with itself.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \ingroup SCENES
	/// \tparam	C	Gameobject type
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename C>
	errcode SetCollisionSelf();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	template <typename C> errcode Scene::SetCollisionTerrain();
	///
	/// \brief	Sets collision terrain.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup SCENES
	/// \tparam	C	Type of the c.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <typename C>
	errcode SetCollisionTerrain();

};

template<typename C1, typename C2>
inline errcode Scene::SetCollisionPair()
{
	errcode err = errcode::success;
	if (collisionManager)
	{
		this->collisionManager->SetCollisionPair<C1, C2>();
	}

	else
	{
		assert(false);
		err = errcode::failure;
	}
	return err;
}

template<typename C>
inline errcode Scene::SetCollisionSelf()
{
	errcode err = errcode::success;
	if (collisionManager)
	{
		this->collisionManager->SetCollisionSelf<C>();
	}

	else
	{
		assert(false);
		err = errcode::failure;
	}
	return err;
}


template<typename C>
inline errcode Scene::SetCollisionTerrain()
{
	errcode err = errcode::success;
	if (collisionManager)
	{
		this->collisionManager->SetCollisionTerrain<C>();
	}

	else
	{
		assert(false);
		err = errcode::failure;
	}
	return err;
}

#endif


