#include "SceneUpdateCommand.h"

#include "Scene.h"
#include "SceneManager.h"

SceneUpdateCommand::SceneUpdateCommand()
{
}

void SceneUpdateCommand::execute()
{
	SceneManager::GetCurrentScene().Update();
}
