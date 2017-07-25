#include "OcclusionScene.h"
#include "CameraManager.h"
#include "Flim.h"
#include "..\FrigateFactory.h"
#include "..\Tester.h"
#include "..\SceneTest.h"
#include "..\EnemyFactory.h"
#include "..\BulletFactory.h"
#include "..\SoundEngine\flimSound.h"
#include "CollisionManager.h"
#include "..\SceneTest.h"
#include "SceneManager.h"

#include "..\SoundEngine\flimSound.h"

errcode OcclusionScene::Initialize()
{


	SetCollisionPair<flimSound, Cottage>();
	//this->frigate = FrigateFactory::CreateFrigate(100, 50, 100);

	this->worldPlane = new SoundTest("__FLIM__textureFlatRender", 0, -20, 0, new SceneTest);
	
	this->cottage = new Cottage();
	this->cottage->Initialize(200, 0, 300, CollisionVolumeType::BSPHERE);
	this->cottage->SceneEntry();




	return errcode::success;
}

OcclusionScene::~OcclusionScene()
{
	DebugMsg::out("Scene Demo Cleaned\n");
};


errcode OcclusionScene::Terminate()
{

	DebugMsg::out("\n\n****************** GAME ENTITIES CLEANUP ******************\n\n");


	if (this->worldPlane)
	{
		delete this->worldPlane;
	}




	return errcode::success;
}

