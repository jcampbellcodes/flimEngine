#include "SceneChangeCommand.h"

#include "Scene.h"
#include "SceneManager.h"

SceneChangeCommand::SceneChangeCommand(Scene * _scene) : scene(_scene)
{
}

void SceneChangeCommand::execute()
{
	// terminate old scene
	SceneManager::GetCurrentScene().Terminate();

	// set scene manager current scene to new scene -- scene manager deletes old scene internally
	SceneManager::SetCurrentScene(scene);

	// initialize new scene
	SceneManager::GetCurrentScene().Initialize();

	// calls update on current scene 
	SceneManager::GetCurrentScene().Update();

	// sets internal scene manager command to old 
	SceneManager::SceneChanged();
}
