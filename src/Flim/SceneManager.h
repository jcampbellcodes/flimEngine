#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <assert.h>
#include <stdio.h>
#include "err.h"
#include "AzulCore.h"
#include "AlarmableManager.h"
#include "InputType.h"
#include "Scene.h"

#include "Executioner.h"

class Updatable;
class Drawable;
class Alarmable;
class Inputable;
class GameObject;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SceneManager
///
/// \brief	Manager for scenes.
///
/// \author	Jack Campbell
/// \date	6/1/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class SceneManager
{
private:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	~SceneManager() 
	{
		//DebugMsg::out("SceneManager cleaned\n"); 
	};
	const SceneManager& operator=(const SceneManager&) = delete;

	static SceneManager* instance;
	static SceneManager& Instance()
	{
		if (!instance)
		{
			instance = new SceneManager();
		}
		return *instance;
	}

	Scene* currentScene;

	// broker for scene change events -- needs to be processed outside of individual scene loop
	friend class SceneChangeCommand;
	friend class SceneUpdateCommand;
	Executioner* executioner;
	Command* currentCommand;
	SceneUpdateCommand* updateCommand;

	errcode privSceneChanged();

	static errcode SceneChanged()
	{
		return Instance().privSceneChanged();
	}


	errcode privChangeScene(Scene* in);

	errcode privSetStartScene(Scene* in);

	errcode privGetCurrentScene(Scene*& out);
	errcode privSetCurrentScene(Scene* in);

	errcode privInitialize();

	errcode privUpdate();

	errcode privDraw();

	errcode privTerminate();

	errcode privRegister(Updatable* in);
	errcode privDeregister(Updatable* in);

	errcode privRegister(GameObject* in);
	errcode privDeregister(GameObject* in);

	errcode privRegister(Drawable* in);
	errcode privDeregister(Drawable* in);

	errcode privRegister(Inputable* in, AZUL_KEY key, input_type type);
	errcode privDeregister(Inputable* in, AZUL_KEY key, input_type type);

	errcode privRegister(float t, Alarmable* in, AlarmableManager::ALARM_ID id);
	errcode privDeregister(Alarmable* in, AlarmableManager::ALARM_ID id);


public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Register(Updatable* in)
	///
	/// \brief	Registers an updatable to the scene.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 
	/// \param [in,out]	in	Updatable to register.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Register(Updatable* in)
	{
		return Instance().privRegister(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Deregister(Updatable * in)
	///
	/// \brief	Deregisters this Updatable to the scene.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	Updatable to deregister.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Deregister(Updatable * in)
	{
		return Instance().privDeregister(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Register(GameObject* in)
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Register(GameObject* in)
	{
		return Instance().privRegister(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Deregister(GameObject * in)
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Deregister(GameObject * in)
	{
		return Instance().privDeregister(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Register(Drawable* in)
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Register(Drawable* in)
	{
		return Instance().privRegister(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Camera& SceneManager::GetMainCamera()
	///
	/// \brief	Gets main camera.
	///\ingroup SCENEMANAGEMENT
	/// \author	Jack Campbell
	/// \date	3/12/2017
	/// 		
	/// \par Shortcut for getting the main camera.
	/// 	 
	/// \code
	/// 	 
	/// 	 Camera* camera = &SceneManager::GetMainCamera();
	/// 	 
	/// \endcode
	///
	/// \return	The main camera.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Camera& GetMainCamera()
	{
		return Instance().GetCurrentScene().GetCamera()->MainCamera();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Camera& SceneManager::Get2DCamera()
	///
	/// \brief	Gets 2D camera.
	///
	/// \author	Jack Campbell
	/// \date	3/12/2017
	/// 		
	/// \par Shortcut for getting the 2D camera.
	/// 	 
	/// 	  \code
	///
	/// 	 Camera* camera = &SceneManager::Get2DCamera();
	///
	/// \endcode
	///
	/// \return	The 2D camera.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Camera& Get2DCamera()
	{
		return Instance().GetCurrentScene().GetCamera()->Get2DCamera();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Deregister(Drawable * in)
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Deregister(Drawable * in)
	{
		return Instance().privDeregister(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Register(Inputable* in, AZUL_KEY key, input_type type)
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in  	If non-null, the in.
	/// \param 		   	key 	The key.
	/// \param 		   	type	The type.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Register(Inputable* in, AZUL_KEY key, input_type type)
	{
		return Instance().privRegister(in, key, type);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Deregister(Inputable* in, AZUL_KEY key, input_type type)
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in  	If non-null, the in.
	/// \param 		   	key 	The key.
	/// \param 		   	type	The type.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Deregister(Inputable* in, AZUL_KEY key, input_type type)
	{
		return Instance().privDeregister(in, key, type);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Register(float t, Alarmable* in, AlarmableManager::ALARM_ID id)
	///
	/// \brief	Registers this object.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param 		   	t 	The float to process.
	/// \param [in,out]	in	If non-null, the in.
	/// \param 		   	id	The identifier.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Register(float t, Alarmable* in, AlarmableManager::ALARM_ID id)
	{
		return Instance().privRegister(t, in, id);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Deregister(Alarmable * in, AlarmableManager::ALARM_ID id)
	///
	/// \brief	Deregisters this object.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	/// \param 		   	id	The identifier.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Deregister(Alarmable * in, AlarmableManager::ALARM_ID id)
	{
		return Instance().privDeregister(in, id);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::SetStartScene(Scene* in)
	///
	/// \brief	Sets start scene.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup SCENEMANAGEMENT
	/// \param [in]	in	Scene to be the start scene.
	/// 			
	/// \par Set the scene that is first displayed after the game is loaded.
	/// 	 
	/// \code
	/// 	 
	/// 	 Flim::LoadResources()
	/// 	 { 
	/// 		SceneDemo* startScene = new SceneDemo();
	/// 		SceneManager::SetStartScene(startScene);
	/// 	 }
	/// 	 
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode SetStartScene(Scene* in)
	{
		return Instance().privSetStartScene(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Scene& SceneManager::GetCurrentScene()
	///
	/// \brief	Gets current scene.
	///\ingroup SCENEMANAGEMENT
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par Returns a reference to the current scene.
	/// 	 
	/// \code
	/// 	 
	/// 	 Scene* scene = &SceneManager::GetCurrentScene();
	/// 	 
	/// \endcode
	///
	/// \return	The current scene.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Scene& GetCurrentScene()
	{
		Scene* scene;
		errcode err = Instance().privGetCurrentScene(scene);
		assert(err == errcode::success);
		assert(scene);
		return *scene;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::ChangeScene(Scene* in)
	///
	/// \brief	Change scene.
	///\ingroup SCENEMANAGEMENT
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in]	in	Scene to set.
	/// 			
	/// \par Call this method to initiate the process of scene changing and initialize the inputted scene.
	/// 	 All active gameobjects will be destroyed or recycled.
	/// 	 
	/// \code
	/// 	 // all enemies have been killed! change the scene!
	/// 	 SceneTest* newScene = new SceneTest();
	/// 	 SceneManager::ChangeScene(newScene);
	/// \endcode
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode ChangeScene(Scene* in)
	{
		return Instance().privChangeScene(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::SetCurrentScene(Scene* in)
	///
	/// \brief	Sets current scene.
	///\ingroup INTERNALS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param [in,out]	in	Scene to set.
	/// 				
	/// \par Used by SceneChange command to change the scene
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode SetCurrentScene(Scene* in)
	{
		return Instance().privSetCurrentScene(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Initialize()
	///
	/// \brief	Initialization callback hook into current scene.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Initialize()
	{
		return Instance().privInitialize();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Update()
	///
	/// \brief	Update callback hook.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Update()
	{
		return Instance().privUpdate();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Draw()
	///
	/// \brief	Draw callback hook.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Draw()
	{
		return Instance().privDraw();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::Terminate()
	///
	/// \brief	Terminate callback hook for the user on their scene.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode Terminate()
	{
		return Instance().privTerminate();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode SceneManager::ShutDownCamera()
	///
	/// \brief	Shut down camera.
	///
	/// \author	Jack Campbell
	/// \date	3/12/2017
	/// 		
	/// \par Shuts down the camera manager.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode ShutDownCamera()
	{
		return Instance().currentScene->cameraManager->ShutDown();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static FlimTerrain* SceneManager::getTerrain()
	///
	/// \brief	Gets the terrain.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	Null if it fails, else the terrain.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static FlimTerrain* getTerrain()
	{
		return Instance().currentScene->GetTerrain();
	}

};

#endif