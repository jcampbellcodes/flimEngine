#include "SceneManager.h"
#include "Scene.h"
#include "err.h"
#include "Updatable.h"
#include "Alarmable.h"
#include "GameObject.h"
#include "SceneChangeCommand.h"
#include "SceneUpdateCommand.h"

SceneManager* SceneManager::instance = nullptr;

errcode SceneManager::privSceneChanged()
{
	// current command was an ephemeral command with the new scene passed in
	delete this->currentCommand;
	this->currentCommand = nullptr;
	assert(!this->currentCommand);

	// return to normal operation
	this->currentCommand = (Command*)updateCommand;

	return errcode::success;
}

errcode SceneManager::privChangeScene(Scene * in)
{
	if (!in)
	{
		return errcode::failure;
	}

	// observer pattern -- command tells scene manager the scene has changed and resumes normal command
	this->currentCommand = new SceneChangeCommand(in);

	return errcode::success;
}

errcode SceneManager::privSetStartScene(Scene * in)
{
	if (in)
	{
		this->currentScene = in;
		return errcode::success;
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privGetCurrentScene(Scene*& out)
{

	if (this->currentScene)
	{
		out = currentScene;
		return errcode::success;
	}
	else
	{
		return errcode::failure;
	}

}

errcode SceneManager::privSetCurrentScene(Scene * in)
{
	if (!in)
	{
		return errcode::failure;
	}
	if (!currentScene)
	{
		return errcode::failure;
	}
	delete currentScene;
	this->currentScene = in;
	return errcode::success;
}

errcode SceneManager::privInitialize()
{
	this->updateCommand = new SceneUpdateCommand();
	this->currentCommand = (Command*)updateCommand;
	this->executioner = new Executioner();


	if (this->currentScene)
	{
		return this->currentScene->Initialize();
	}
	else
	{
		return errcode::nullscene;
	}

}

errcode SceneManager::privUpdate()
{
	executioner->ExecuteCommands();
	

	// this will either be a simple command to update the scene
	// but could also be a command to change the current scene and then update from there
	executioner->addCommand(currentCommand);
	return errcode::success;

}

errcode SceneManager::privDraw()
{

	if (this->currentScene)
	{
		return this->currentScene->Draw();
	}
	else
	{
		return errcode::nullscene;
	}
	
}

errcode SceneManager::privTerminate()
{
	if (this->executioner)
	{
		delete this->executioner;
	}

	if (this->updateCommand)
	{
		delete this->updateCommand;
	}

	if (this->currentScene)
	{
		this->currentScene->Terminate();
		delete this->currentScene;
	}

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
	//DebugMsg::out("\n\n****************** CLEANED ******************\n\n");
	return errcode::success;
}

errcode SceneManager::privRegister(Updatable * in)
{
	if (this->currentScene)
	{
		return this->currentScene->Register(in);
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privDeregister(Updatable * in)
{
	if (this->currentScene)
	{
		return this->currentScene->Deregister(in);
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privRegister(Drawable * in)
{
	if (this->currentScene)
	{
		return this->currentScene->Register(in);
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privDeregister(Drawable * in)
{
	if (this->currentScene)
	{
		return this->currentScene->Deregister(in);
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privRegister(GameObject * in)
{
	if (this->currentScene)
	{
		return this->currentScene->Register(in);
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privDeregister(GameObject * in)
{
	if (this->currentScene)
	{
		return this->currentScene->Deregister(in);
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privRegister(Inputable * in, AZUL_KEY key, input_type type)
{
	if (this->currentScene)
	{
		return this->currentScene->Register(in, key, type);
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privDeregister(Inputable * in, AZUL_KEY key, input_type type)
{
	if (this->currentScene)
	{
		return this->currentScene->Deregister(in, key, type);
	}
	else
	{
		return errcode::nullscene;
	}
}


errcode SceneManager::privRegister(float t, Alarmable * in, AlarmableManager::ALARM_ID id)
{
	if (this->currentScene)
	{
		return this->currentScene->Register(t, in, id);
	}
	else
	{
		return errcode::nullscene;
	}
}

errcode SceneManager::privDeregister(Alarmable * in, AlarmableManager::ALARM_ID id)
{
	if (this->currentScene)
	{
		return this->currentScene->Deregister(in, id);
	}
	else
	{
		return errcode::nullscene;
	}
}