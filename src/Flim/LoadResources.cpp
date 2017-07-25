#include "Flim.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "ImageManager.h"
#include "TerrainManager.h"
#include "../SceneDemo.h"
#include "../SceneTest.h"
#include "SceneNull.h"
#include "SceneManager.h"
#include "../TankScene.h"
#include "../IntroScene.h"
#include "OcclusionScene.h"
#include "..\SoundEngine\SoundEngine.h"
#include "..\SoundEngine\SoundCallRegistry.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void Flim::LoadResources()
///
/// \brief	Loads the resources.
///
/// \author	Jack Campbell
/// \date	3/6/2017
/// 		
/// 		Define this method to load assets and do any initialization that requires your assets to be loaded.
/// 		
/// 		\code
///
/// void Flim::LoadResources()
/// {
///	//---------------------------------------------------------------------------------------------------------
///	// Load the Models
///	//---------------------------------------------------------------------------------------------------------
///
///	ModelManager::LoadModel("space_frigate", "space_frigate.azul");
///	ModelManager::LoadModel("Axis", "Axis.azul");
///	ModelManager::LoadModel("Plane", "Plane.azul");
///	ModelManager::LoadModel("Cottage", "Cottage.azul");
///	ModelManager::LoadModel("Sphere", "sphere.azul");
///
///	//---------------------------------------------------------------------------------------------------------
///	// Load the Textures
///	//---------------------------------------------------------------------------------------------------------
///
///	TextureManager::LoadTexture("space_frigate", "space_frigate.tga");
///	TextureManager::LoadTexture("Cottage", "stitch.tga");
///	TextureManager::LoadTexture("grid", "grid.tga");
///	TextureManager::LoadTexture("Sphere", "sphere.tga");
///
///	//---------------------------------------------------------------------------------------------------------
///	// Load the Shaders
///	//---------------------------------------------------------------------------------------------------------
///
///	ShaderManager::LoadShader("textureFlatRender", "textureFlatRender");
///	ShaderManager::LoadShader("textureLightRender", "textureLightRender");
///	ShaderManager::LoadShader("colorNoTextureRender", "colorNoTextureRender");
///	ShaderManager::LoadShader("colorConstantRender", "colorConstantRender");
///
///
///	SceneManager::SetStartScene(new FirstScene);
/// }
///
/// \endcode
////////////////////////////////////////////////////////////////////////////////////////////////////

void Flim::LoadResources()
{
	// sound test scene
	//SceneManager::SetStartScene(new OcclusionScene);
	
	// collision test scene
	//SceneManager::SetStartScene(new SceneDemo);
	
	// tank game
	SceneManager::SetStartScene(new IntroScene);
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------
	ModelManager::LoadDefaultModels();
	ModelManager::LoadModel("space_frigate", "space_frigate.azul");
	ModelManager::LoadModel("Axis", "Axis.azul");
	ModelManager::LoadModel("Plane", "Plane.azul");
	ModelManager::LoadModel("Cottage", "Cottage.azul");
	ModelManager::LoadModel("Sphere", "sphere.azul");
	ModelManager::LoadModel("TankBody", "t99body.azul");
	ModelManager::LoadModel("TankTurret", "t99turret.azul");

	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------

	TextureManager::LoadTexture("space_frigate", "space_frigate.tga");
	TextureManager::LoadTexture("Cottage", "Stone.tga");
	TextureManager::LoadTexture("TestHeightmap", "TEST.tga");
	TextureManager::LoadTexture("TestHeightmap2", "test_bigger.tga");
	TextureManager::LoadTexture("grid", "grid.tga");
	TextureManager::LoadTexture("Sphere", "sphere.tga");
	TextureManager::LoadTexture("TankBodyRed", "body_red.tga");
	TextureManager::LoadTexture("TankBody", "body.tga");
	TextureManager::LoadTexture("TankTurret", "track.tga");
	TextureManager::LoadTexture("ground", "dirt_1.tga");
	TextureManager::LoadTexture("ground2", "dirt2.tga");
	TextureManager::LoadTexture("ground3", "dirt3.tga");
	TextureManager::LoadTexture("Explosion1", "exp1.tga");
	TextureManager::LoadTexture("Explosion2", "exp2.tga");
	TextureManager::LoadTexture("Explosion3", "exp3.tga");


	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------
	ShaderManager::LoadDefaultShaders();
	
	
	TerrainManager::LoadTerrain("Level1", "level1.tga", "ground", 10000.0f, 1000.0f, 0.0f, 10.0f, 10.0f);
	ImageManager::Load("Level1Minimap", "..\\Heightmaps\\level1.tga");
	TerrainManager::LoadTerrain("Level2", "level_2.tga", "ground2", 10000.0f, 1000.0f, 0.0f, 10.0f, 10.0f);
	ImageManager::Load("Level2Minimap","..\\Heightmaps\\level_2.tga");
	TerrainManager::LoadTerrain("Level3", "level3.tga", "ground3", 10000.0f, 1000.0f, 0.0f, 10.0f, 10.0f);
	TerrainManager::LoadTerrain("TestTerrain", "hm_simple.tga", "ground3", 300.0f, 100.0f, 0.0f, 10.0f, 10.0f);
	ImageManager::Load("Level3Minimap", "..\\Heightmaps\\level3.tga");

	ImageManager::Load("PlayerIcon", "player_icon.tga");
	ImageManager::Load("EnemyIcon", "enemy_icon.tga");
	ImageManager::Load("IntroOverlay", "INTROOVERLAY.tga");

	ImageManager::Load("stitch", "stitch.tga");
	ImageManager::Load("Health", "health.tga");
	ImageManager::Load("Tank", "tank.tga");
	ImageManager::Load("Logo", "logo.tga");
	ImageManager::Load("Winner", "winner.tga");
	ImageManager::Load("Spacebar", "pressspacebar.tga");
	ImageManager::Load("alien", "Aliens.tga", new Rect(136.0f, 64.0f, 85.0f, 63.0f));

	SoundEngine::LoadSound("BattleField_Action.wav", SoundCallID::Ambience);
	SoundEngine::LoadSound("bossmusic_1.wav", SoundCallID::Level1Music);
	SoundEngine::LoadScript("Music.txt", SoundCallID::Music);
	SoundEngine::LoadSound("hit_1.wav", SoundCallID::Hit1);
	SoundEngine::LoadSound("hit_2.wav", SoundCallID::Hit2);
	SoundEngine::LoadSound("hit_3.wav", SoundCallID::Hit3);
	SoundEngine::LoadSound("shot_1.wav", SoundCallID::Shoot1);
	SoundEngine::LoadSound("shot_2.wav", SoundCallID::Shoot2);
	SoundEngine::LoadSound("shot_3.wav", SoundCallID::Shoot3);
	SoundEngine::LoadSound("tank_roll.wav", SoundCallID::TankMove);
	SoundEngine::LoadSound("Race2.wav", SoundCallID::Level2Music);
	SoundEngine::LoadSound("BossBattleIntense.wav", SoundCallID::Level3Music);
	SoundEngine::LoadSound("FunkyGarage_mono.wav", SoundCallID::GarageMusic);



}