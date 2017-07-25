#include "SceneDemo.h"
#include "Flim\CameraManager.h"
#include "Flim\Flim.h"
#include "FrigateFactory.h"
#include "Tester.h"

#include "Flim\SceneManager.h"

errcode SceneDemo::Initialize()
{


	//this->frigate = new Frigate();
	this->worldPlane = new WorldPlane();
	return errcode::success;
}

SceneDemo::~SceneDemo()
{
	DebugMsg::out("Scene Demo Cleaned\n");
};


errcode SceneDemo::Terminate()
{

	DebugMsg::out("\n\n****************** GAME ENTITIES CLEANUP ******************\n\n");

	SceneManager::GetCurrentScene().GetCamera()->ShutDown();


	FrigateFactory::Terminate();

	/*
	if (this->frigate)
	{
		delete this->frigate;
	}
	*/

	if (this->worldPlane)
	{
		delete this->worldPlane;
	}




	return errcode::success;
}

