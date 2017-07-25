#include "Scene.h"
#include "UpdatableManager.h"
#include "Executioner.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Visualizer.h"
#include "Terrain.h"
#include "TerrainManager.h"

Scene::Scene() : terrain(nullptr)
{
	updateManager = new UpdatableManager();
	drawManager = new DrawableManager();
	alarmManager = new AlarmableManager();

	collisionManager = new CollisionManager();

	keyboardManager = new KeyboardEventManager();

	cameraManager = new CameraManager();

	executioner = new Executioner();
}

Scene::~Scene()
{
	if (terrain)
	{
		terrain = nullptr;
	}
	if (updateManager)
	{
		delete updateManager;
		updateManager = nullptr;
	}
	if (collisionManager)
	{
		delete collisionManager;
		collisionManager = nullptr;
	}
	if (drawManager)
	{
		delete drawManager;
		drawManager = nullptr;
	}
	if (alarmManager)
	{
		delete alarmManager;
		alarmManager = nullptr;
	}
	if (keyboardManager)
	{
		delete keyboardManager;
		keyboardManager = nullptr;
	}
	if (executioner)
	{
		delete executioner;
		executioner = nullptr;
	}

	//DebugMsg::out("Scene cleaned\n");
}

errcode Scene::SetTerrain(const char * terrainName)
{
	TerrainManager::GetTerrain(this->terrain, terrainName);

	if (terrain)
	{
		return this->terrain->ActivateTerrain();
	}
	else
	{
		return errcode::notfound;
	}


}

errcode Scene::Register(Updatable* in)
{
	updateManager->Register(in);
	return errcode::success;
}

errcode Scene::Deregister(Updatable* in)
{
	updateManager->Deregister(in);
	return errcode::success;
}

errcode Scene::Register(GameObject* in)
{
	in->SubmitEntry();
	return errcode::success;
}

errcode Scene::Deregister(GameObject* in)
{
	in->SubmitExit();
	return errcode::success;
}

errcode Scene::Register(Drawable* in)
{
	drawManager->Register(in);
	return errcode::success;
}

errcode Scene::Deregister(Drawable* in)
{
	drawManager->Deregister(in);
	return errcode::success;
}

errcode Scene::Register(float t, Alarmable* in, AlarmableManager::ALARM_ID id)
{
	alarmManager->Register(t, in, id);
	return errcode::success;
}

errcode Scene::Deregister(Alarmable* in, AlarmableManager::ALARM_ID id)
{
	alarmManager->Deregister(in, id);
	return errcode::success;
}

errcode Scene::Register(Inputable * in, AZUL_KEY key, input_type type)
{
	keyboardManager->Register(in, key, type);
	return errcode::success;
}

errcode Scene::Deregister(Inputable * in, AZUL_KEY key, input_type type)
{
	keyboardManager->Deregister(in, key, type);
	return errcode::success;
}

void Scene::SubmitCommand(Command * in)
{
	executioner->addCommand(in);
}

errcode Scene::Update()
{

	executioner->ExecuteCommands();

	alarmManager->ProcessAlarms();

	keyboardManager->ProcessKeys();

	collisionManager->Update();

	updateManager->ProcessElements();
	return errcode::success;
}

errcode Scene::Draw()
{
	Visualizer::VisualizeAll();

	if (this->terrain)
	{
		terrain->Draw();
	}

	drawManager->ProcessElements();

	return errcode::success;
}
