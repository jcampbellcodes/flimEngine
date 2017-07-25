#include "AzulCore.h"
#include "Flim.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "CameraManager.h"
#include "Updatable.h"
#include "Drawable.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "Visualizer.h"
#include "TerrainManager.h"
#include "..\SoundEngine\SoundEngine.h"

#include "TimeManager.h"


Flim* Flim::instance = nullptr;

Flim::~Flim()
{
	//DebugMsg::out("Game cleaned\n");
}

Vect Flim::privGetColor()
{
	Vect col(color[0], color[1], color[2], color[3]);
	return col;
}

std::string Flim::privGetWindowName()
{
	return name;
}

//-----------------------------------------------------------------------------
// Flim::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Flim::Initialize()
{
	this->GameInitialize();
}

//-----------------------------------------------------------------------------
// Flim::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Flim::LoadContent()
{

	SoundEngine::Create();
	this->LoadResources();

	SceneManager::Initialize();
}

//-----------------------------------------------------------------------------
// Flim::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Flim::Update()
{

	SceneManager::Update();
	SoundEngine::Update();
	FlimTime::ProcessTime();
}

//-----------------------------------------------------------------------------
// Flim::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Flim::Draw()
{
	SceneManager::Draw();
}



//-----------------------------------------------------------------------------
// Flim::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Flim::UnLoadContent()
{
	this->GameTerminate();

	FlimTime::Terminate();
	//DebugMsg::out("\n\n****************** GAME MANAGERS CLEANUP ******************\n\n");
	// general clean up.
	ShaderManager::UnloadShaders();
	TextureManager::UnloadTextures();
	ModelManager::UnloadModels();
	TerrainManager::UnloadTerrains();
	ImageManager::UnloadImages();
	Visualizer::Terminate();

	SceneManager::Terminate();

	SoundEngine::Terminate();
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}


}


