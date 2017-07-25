#pragma once

/** \defgroup FLIM_API flim API
\brief The is the interface to be used for nearly all flim tasks
*/

/** \defgroup GAMEOBJECT GameObject
\ingroup FLIM_API

*/


/** \defgroup SPRITES Sprites
\ingroup FLIM_API

\brief Sprite objects are 2D images orthographically rendered to the screen.

*/


/** \defgroup SOUNDS Sound
\ingroup FLIM_API

\brief Description of the sound engine

*/


/** \defgroup FLIMSOUND flimSounds
\ingroup SOUNDS

\brief flimSounds provide audio playback and processing functionality.

*/

/** \defgroup FLIMFILTER flimFilter
\ingroup SOUNDS

\brief Objects used with flimSounds to configure filtering effects.

*/

/** \defgroup FLIMLISTENER 3D Listener
\ingroup SOUNDS

\brief The flimListener is an object whose position and orientation must be specified by the user to correctly configure 3D sound.

*/


/** \defgroup TERRAIN Terrain
\ingroup FLIM_API

\brief Terrains can create models from heightmap textures loaded by the user and offer support methods for common terrain calculations.

*/


/** \defgroup TOOLS Tools
\ingroup FLIM_API

*/

/** \defgroup ENGINE Global Methods
\ingroup FLIM_API

*/

/** \defgroup BASICS Basic Properties
\ingroup GAMEOBJECT

\brief GameObjects have certain properties that can be registered for callbacks,
such as input, alarms, and collisions.

*/

/** \defgroup BASICSCALLBACKS Callbacks
\ingroup BASICS

\brief SceneEntry, SceneExit, Update, Draw

\par These callbacks are the basic inherited callbacks of a GameObject derived class.

*/

/** \defgroup BASICSREGISTRATION Registration
\ingroup BASICS

\brief The inherited callbacks must be registered for 

*/


/** \defgroup INPUTEVENTS Input Events
\ingroup GAMEOBJECT

\brief Registering for keys, demos for keycallbacks

*/


/** \defgroup INPUTREGISTRATION Registration
\ingroup INPUTEVENTS

\brief Registering for keys, demos for keycallbacks

*/

/** \defgroup INPUTCALLBACKS Callbacks
\ingroup INPUTEVENTS

\brief Registering for keys, demos for keycallbacks

*/

/** \defgroup INPUTTYPES Types
\ingroup INPUTEVENTS

\brief Registering for keys, demos for keycallbacks

*/

/** \defgroup ALARMEVENTS Alarm Events
\ingroup GAMEOBJECT

\brief Registering for alarms, setting up alarm callbacks

*/

/** \defgroup ALARMREGISTRATION Registration
\ingroup ALARMEVENTS

\brief Registering for alarms, setting up alarm callbacks

*/

/** \defgroup ALARMCALLBACKS Callbacks
\ingroup ALARMEVENTS

\brief Registering for alarms, setting up alarm callbacks

*/

/** \defgroup COLLISIONCALLBACKS Callbacks
\ingroup COLLISIONS

\brief Registering for alarms, setting up alarm callbacks

*/

/** \defgroup COLLISIONREGISTRATION Registration
\ingroup COLLISIONS

\brief Registering for alarms, setting up alarm callbacks

*/

/** \defgroup COLLISIONS Collision Events
\ingroup GAMEOBJECT

\brief Registering for collision, uing the callbacks

*/

/** \defgroup RESOURCES Resources
\ingroup FLIM_API

\brief GameInitialize, ResourceManagers, LoadAllResources

*/

/** \defgroup RESOURCEMANAGERS Resource Managers
\ingroup RESOURCES

\brief GameInitialize, ResourceManagers, LoadAllResources

*/

/** \defgroup ENGINECALLBACKS Engine Callbacks
\ingroup RESOURCES

\brief GameInitialize, ResourceManagers, LoadAllResources

*/

/** \defgroup SCENE Scene
\ingroup FLIM_API
\brief Initialize, Terminate, Camera, Collisions

*/


/** \defgroup SCENES Scenes
\ingroup SCENE
\brief Individual scene stuff.

*/

/** \defgroup CAMERA Camera
\ingroup SCENES
\brief Individual scene stuff.

*/

/** \defgroup SCENEMANAGEMENT Scene Management
\ingroup SCENE
\brief Individual scene stuff.

*/

/** \defgroup GETTINGSTARTED Getting Started
\brief Do a writeup on how to start a scene with a single
		graphics object.
*/





/** \defgroup INITALIZATION Loading and Initialization
\ingroup GETTINGSTARTED
\brief How to load resources and set basic properties for your game

\par The first step in starting a flimEngine project is setting the basic window settings
and loading the resources that you will need such as models, textures, and shaders. There are two exposed 
engine callbacks where this initialization is most important.

Called first is the Flim::GameInitialize callback, defined in FlimResources/GameInitialize.cpp
Fill out this method with non-graphics related loading and initialization, set the window height, and whatever
else you need to initialize on game start. For our demo, we will set the window name, the aspect ratio of the window, and the default color of the background.

\code

void Flim::GameInitialize()
{
	// Flim Window Device setup
	this->setWindowName("flimEngine Demo");
	this->setWidthHeight(800, 600);
	this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);
}

\endcode


After Flim::GameInitialize is called by flimEngine, the Flim::LoadResources callback is called; you can access this method via FlimResources/LoadResources.cpp
Place in this callback any graphics related loading as well as the start scene

\code

void Flim::LoadResources()
{
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------
	
	ModelManager::LoadModel("space_frigate", "space_frigate.azul");
	ModelManager::LoadModel("Axis", "Axis.azul");
	ModelManager::LoadModel("Plane", "Plane.azul");
	ModelManager::LoadModel("Cottage", "Cottage.azul");
	ModelManager::LoadModel("Sphere", "sphere.azul");
	
	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------
	
	TextureManager::LoadTexture("space_frigate", "space_frigate.tga");
	TextureManager::LoadTexture("Cottage", "stitch.tga");
	TextureManager::LoadTexture("grid", "grid.tga");
	TextureManager::LoadTexture("Sphere", "sphere.tga");
	
	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------
	
	ShaderManager::LoadShader("textureFlatRender", "textureFlatRender");
	ShaderManager::LoadShader("textureLightRender", "textureLightRender");
	ShaderManager::LoadShader("colorNoTextureRender", "colorNoTextureRender");
	ShaderManager::LoadShader("colorConstantRender", "colorConstantRender");
	
	
	SceneManager::SetStartScene(new FirstScene);
}

\endcode


*/








/** \defgroup DEFINESCENES Defining a Scene
\ingroup GETTINGSTARTED
\brief How to define a single empty scene by deriving from flimEngine's Scene class


\par In flimEngine, games are driven by GameObjects that live in Scene objects. You just need to include Flim\Scene.h and derive from a Scene.

Here is an example of a Scene called FirstScene

Here is FirstScene.h
\code

#include "Flim\Scene.h"

class FirstScene : public Scene
{
	public:
	FirstScene() = default;
	FirstScene(const FirstScene&) = default;
	virtual ~FirstScene() override;
	const FirstScene& operator=(const FirstScene&) = delete;
	
	// Called when a scene starts
	errcode Initialize() override;
	
	// Callbed when a scene ends
	errcode Terminate() override;

};

\endcode


Here is FirstScene.cpp
\code

#include "FirstScene.h"

// Called when the scene becomes active
errcode FirstScene::Initialize()
{
	DebugMsg::out("First Scene Started!\n");
	return errcode::success;
}

FirstScene::~FirstScene()
{
};


// Called when scene is changed or game is terminated
errcode FirstScene::Terminate()
{
	DebugMsg::out("First Scene Killed!\n");
	return errcode::success;
}


\endcode


*/






/** \defgroup DEFINEGOS Defining a Basic GameObject
\ingroup GETTINGSTARTED
\brief How to define a basic GameObject


GameObjects are the building blocks used to create games with flimEngine.

Currently, all properties of GameObjects can be activated/deactivated by registering and deregistering.
The most basic callbacks to register a GameObject for are GameObject::Update ( for non-rendering code that should be called every frame ) and GameObject::Draw ( for rendering code that should be updated every frame )

Before going into registration, let's make a simple empty GameObject called Frigate (Sorry Andre)

\code

#include "AzulCore.h"
#include "Flim/GameObject.h"

class Frigate : public GameObject
{
	private:
	
	// These members are for the underlying Azul graphics layer (graphics objects, matrices, and vectors)
	GraphicsObject_TextureLight *pGObj_SpaceFrigateLight;
	Matrix ShipScale;
	Vect ShipPos;
	Matrix ShipRot;
	const float ShipTransSpeed = 5;
	const float ShipRotAng = .05f;


	public:
	Frigate();
	Frigate(const Frigate&);
	virtual ~Frigate();
	const Frigate& operator=(const Frigate&);
	
	// Called once per frame (don't put rendering code here!)
	virtual errcode Update() override;
	
	// Called once per frame (put rendering code here)
	virtual errcode Draw() override;
	
	// Called when this GameObject enters a scene
	errcode SceneEntry() override;
	
	// Called when this GameObject leaves a scene
	errcode SceneExit() override;

};

\endcode


Now in order for the Update and Draw callbacks to become active, we have to register for them either on construction or when the GameObject enters a scene (whichever is more appropriate)
REMEMBER: Every registration should have an associated deregistration when the GameObject is no longer active!


\code

// Include your header
#include "Frigate.h"

// Resource managers used to load what the graphics object needs
#include "Flim\ModelManager.h"
#include "Flim\TextureManager.h"
#include "Flim\ShaderManager.h"

// Includes for the camera and scene (used in the Draw callback)
#include "Flim\CameraManager.h"
#include "Flim\SceneManager.h"
#include "Flim\Scene.h"


Frigate::Frigate()
{

	// A bunch of gunk to initialize the frigate's graphics object.

	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(&ModelManager::GetModel("space_frigate"), &ShaderManager::GetShader("textureLightRender"), &TextureManager::GetTexture("space_frigate"), LightColor, LightPos);
	// Creating matrices for in-world placement
	Matrix world;
	// Spaceship
	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipRot.set(IDENTITY);
	ShipPos.set((float)x, (float)y, (float)z);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

}

Frigate::~Frigate()
{
}

errcode Frigate::Update()
{

	// Place frame related content here. This code moves the ship's graphics object.

	// Ship translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
	ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		ShipPos += Vect(0, 0, 1) * ShipRot * -ShipTransSpeed;
	}
	
	// Ship Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		ShipRot *= Matrix(ROT_Y, ShipRotAng);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		ShipRot *= Matrix(ROT_Y, -ShipRotAng);
	}
	
	// Spaceship adjust matrix
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);
	
	return errcode::success;
}

errcode Frigate::Draw()
{

	// Place rendering code here.

	// Render ship's graphics object to the current main camera via the Scene
	pGObj_SpaceFrigateLight->Render(&SceneManager::GetCurrentScene().GetCamera()->MainCamera());
	
	return errcode::success;
}

errcode Frigate::SceneEntry()
{

	// Registration
	SubmitUpdateRegistration();
	SubmitDrawRegistration();


	// Setting graphics member variables
	Matrix world;
	ShipPos.set(0, 20, 0);
	world = Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	return errcode::success;
}

errcode Frigate::SceneExit()
{
	// Deregistration
	SubmitUpdateDeregistration();
	SubmitDrawDeregistration();

	return errcode::success;
}


\endcode



*/








/** \defgroup GOPROPS Register GameObject Properties
\ingroup GETTINGSTARTED
\brief GameObjects have extra properties that they can be registered for, such as Alarms (callbacks that fire after a certain time), player input, and collision with other GameObjects
*/









/** \defgroup REGALARMS Register For Alarms
\ingroup GOPROPS
\brief How to register our Frigate for alarms

Alarms are callbacks you can register to fire off after a certain time. To start, first override the inherited Alarm callbacks (however many you need)

\code

#include "AzulCore.h"
#include "Flim/GameObject.h"

class Frigate : public GameObject
{
//...

	void Alarm0() override;
	void Alarm1() override;
	void Alarm2() override;

//...

};

\endcode

Next, register the alarms wherever appropriate. For an example, we can register in the GameObject::SceneEntry callback.

\code

errcode Frigate::SceneEntry()
{
//...

	SubmitAlarmRegistration(1000.0f, AlarmableManager::ALARM_0);
	SubmitAlarmRegistration(5000.0f, AlarmableManager::ALARM_1);
	SubmitAlarmRegistration(8000.0f, AlarmableManager::ALARM_2);
//...
}

\endcode

Remember also to deregister your alarms in case the GameObject dies before the alarms fire.

\code
errcode Frigate::SceneExit()
{

//...

	SubmitAlarmDeregistration(AlarmableManager::ALARM_0);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_1);
	SubmitAlarmDeregistration(AlarmableManager::ALARM_2);

//...
	return errcode::success;
}
\endcode


Now finally, when you define the callbacks for each alarm, your code will be called. In this case, Alarm0 fires after 1 second (1000ms), Alarm1 after 5 seconds (5000ms), and Alarm2 after 8 seconds (8000ms)

\code

void Frigate::Alarm0()
{
	DebugMsg::out("\n\nFIRST FRIGATE ALARMED\n\n");
}

void Frigate::Alarm1()
{
	DebugMsg::out("\n\nSECOND FRIGATE ALARMED\n\n");
}

void Frigate::Alarm2()
{
	DebugMsg::out("\n\nTHIRD FRIGATE ALARMED\n\n\n");
}

\endcode

*/












/** \defgroup REGINPUT Register For Input
\ingroup GOPROPS
\brief How to register GameObjects for single key events


GameObjects can register for callbacks when keys are pressed or released. Just register/deregister in an appropriate place as before, override the callbacks you want, and put your code in the definitions

1 -- Registration/Deregistration
\code


errcode Frigate::SceneEntry()
{
//...
	SubmitInputRegistration(AZUL_KEY::KEY_SPACE, input_type::pressed);
	SubmitInputRegistration(AZUL_KEY::KEY_SPACE, input_type::released);
//...
	return errcode::success;
}

errcode Frigate::SceneExit()
{
//...

	SubmitInputDeregistration(AZUL_KEY::KEY_E, input_type::pressed);
	SubmitInputDeregistration(AZUL_KEY::KEY_E, input_type::released);

//...
	return errcode::success;
}


\endcode

2 -- Override callbacks
\code

class Frigate : public GameObject
{
//...
	errcode KeyPressed(AZUL_KEY key) override;
	errcode KeyReleased(AZUL_KEY key) override;
//...
};


\endcode


3 -- Write your code in the definitions
\code

errcode Frigate::KeyPressed(AZUL_KEY key)
{
	if (key == AZUL_KEY::KEY_SPACE)
	{
		DebugMsg::out("pressed\n");
	}
	return errcode::success;
}

errcode Frigate::KeyReleased(AZUL_KEY key)
{
	if (key == AZUL_KEY::KEY_SPACE)
	{
		DebugMsg::out("released\n");
	}
	return errcode::success;
}

\endcode



*/













/** \defgroup REGCOLLISIONS Register For Collision
\ingroup GOPROPS
\brief How to register GameObjects for collision.

GameObjects that have models can register for collisions with other GameObjects, and there are several steps for registration.

First, GameOjet types must be registered as collidable in some sort of initialization code. For example, we could do it in the Scene::Initialize of our FirstScene

\code

#include "Flim/CollisionManager.h"
#include "Frigate.h"
#include "Cottage.h"

errcode SceneDemo::Initialize()
{

	// Allows frigates to register for collision with other frigates
	SetCollisionSelf<Frigate>();

	// Allows cottages and frigates to register for collisions with one another
	SetCollisionPair<Cottage, Frigate>();

	// Allows Frigates to collide with the Terrain
	SetCollisionTerrain<Frigate>();

	return errcode::success;
}

\endcode


Then, the GameObjects themselves need to declare the callbacks for the collision events.

Our Frigate, for example, would define a callback for collisions with Cottages and other Frigates.

\code

#include "AzulCore.h"
#include "Flim/GameObject.h"

class Frigate : public GameObject
{
//...

	virtual errcode Collision(Frigate*)
	{
		DebugMsg::out("Collision Frigate with Frigate\n");
		return errcode::success;
	}

	virtual errcode CollisionEnter(Cottage*)
	{
		DebugMsg::out("Collision Entered With Cottage\n");
		return errcode::success;
	}

	virtual errcode CollisionExit()
	{
		DebugMsg::out("Frigate just stopped colliding.\n");
		return errcode::success;
	}

	virtual errcode CollisionTerrain(const CollisionVolumeAABB&)
	{
		DebugMsg::out("Frigate collides with Terrain, and here is the AABB that caused the collision\n");
		return errcode::success;
	}

	virtual errcode Collision(Cottage*)
	{
		DebugMsg::out("Collision Frigate with Frigate\n");
		return errcode::success;
	}
//...
};
\endcode

And finally, some bookkeeping must be done so the collision system knows about the GameObject's model. You need to register, deregister
for collisions, set the model to be used for collision, and continually tell the collision system about the model's world matrix (if the model will move);

\code

Frigate::Frigate()
{
	// set model to be used for collision
	// Four collision volumes are available: OBB, AABB, BSphere, and OcclusionLine
	SetColliderModel(pGObj_SpaceFrigateLight->getModel(), VolumeType::OBB);

}


\endcode

\code

errcode Frigate::Update()
{
	//...
	// however you are calculating the world matrix of the model
	Matrix world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceFrigateLight->SetWorld(world);

	// give that world matrix to the collision system
	UpdateCollisionData(world);

	return errcode::success;
}

\endcode
\code
errcode Frigate::SceneEntry()
{
	// submit yourself for registration
	SubmitCollisionRegistration<Frigate>(this);
	return errcode::success;

}
\endcode
\code
errcode Frigate::SceneExit()
{

	// submit yourself for deregistration
	SubmitCollisionDeregistration<Frigate>(this);
	return errcode::success;
}
\endcode
*/
















/** \defgroup CHANGESCENES Changing Scenes
\ingroup GETTINGSTARTED
\brief How to change a scene


Changing scenes is done through the SceneManager and just requires a pointer to the new scene. For example, if we wanted the scene to change when the frigate dies, we could write this:

\code
// Frigate.cpp
// include your next scene
#include "SecondScene.h" 
#include "Flim\SceneManager.h"

errcode Frigate::SceneExit()
{
	//...
	
	// pass a pointer to the new scene.
	SceneManager::ChangeScene(new SecondScene);

	//...
}

\endcode


*/

/** \defgroup INTERNAL Internals
\brief You hopefully won't need to look at these.

*/



/*




TERRAIN!




*/



/** \defgroup TERRAINTUT Using Terrain
\ingroup GETTINGSTARTED
\brief How to use terrain

Terrains are models generated from a heightmap texture and GameObjects can interact with it through support methods. Each scene can have 1 or 0 terrains.

*/




/** \defgroup LOADINGTERRAIN Loading Terrain
\ingroup TERRAINTUT
\brief How to load a terrain

To load a Terrain, call the LoadTerrain method and specify a string key to referece the terrain, the name of the heightmap (.tga) relative to the Heightmaps folder,
the scale of the terrain, the maximum height, the altitude of the terrain at height zero, and U and V repeating values.

\code
void Flim::LoadResources()
{
	TerrainManager::LoadTerrain("Level1", "level1.tga", "ground", 10000.0f, 1000.0f, 0.0f, 10.0f, 10.0f);
//...
}
\endcode

*/


/** \defgroup SETTINGTERRAIN Setting Terrain at Scene Level
\ingroup TERRAINTUT
\brief How to set terrain

Next, the Scene has built in support methods for setting the Terrain for each scene. If no terrain is set, the terrain is set to nullptr for that scene.
The string used to identify which terrain to activate is the key used in the LoadResources section.

\code

errcode ExampleScene::Initialize()
{
	SetTerrain("Level1");
}

\endcode

*/


/** \defgroup USINGTERRAIN Using Terrain
\ingroup TERRAINTUT
\brief How to access terrain functionality

The current Terrain can be accessed through the scene manager as long as "FlimTerrain.h" is included.
Support methods for the terrain can then be accessed to interact with the Terrain.
See the collision section for information about terrain collision detection.

At run time, these support methods allow you to find a GameObject's position clamped to the terrain or find the normal of the terrain under the game object

\code


errcode Tank::Update()
{
	Vect exactPos;
	// pos is the current position of the tank
	errcode err = SceneManager::getTerrain()->GetExactPosition(pos, exactPos);


	Vect normal;
	SceneManager::getTerrain()->FindNormalUnderPosition(pos, normal);
	// use the normal to orient the tank to the terrain's normal

	//...
}


\endcode

*/





/*



	SOUND



*/

/** \defgroup SOUND Using Sounds
\ingroup GETTINGSTARTED
\brief How to use sounds in flimEngine

flimEngine has a built-in multithreaded sound engine built on top of Microsoft's XAudio2 with scripting capabilities. 

After proper initialization, flimSound objects can be created on the fly and processed with little effort.

*/



// LOADING, INITIALIZATION
/** \defgroup LOADINGSOUND Initializing Sounds
\ingroup SOUND
\brief Initialize the flim Sound engine

There are a few steps to get the flimSound engine up and running. First, you must include flimSound.h in any files that use sounds.

First, sound IDs for possible sounds to be played at runtime must be added to the SoundCallID structure in SoundCallRegistry.h

\code

typedef enum SoundCallID
{
	MenuMusic,
	Explosion,
	Ambience
} SoundCallID;

\endcode

Now these IDs can be attached to audio files or scripts in LoadResources.

\code
void Flim::LoadResources()
{
	// loads an audio file and assigns it to the MenuMusic ID
	SoundEngine::LoadSound("menumusic.wav", SoundCallID::MenuMusic);


	// loads a text file that could have multiple looping audio files and time based processing
	SoundEngine::LoadScript("ambience.txt", SoundCallID::Ambience);
}
\endcode

See the next section, General Playback to see how to use these loaded sounds.

*/


// GENERAL PLAYBACK
/** \defgroup SOUNDPLAYBACK Basic Sound Playback
\ingroup SOUND
\brief How to use the playback properties of flimSounds

A flimSound can be accessed via its ID once it has been loaded in any file that includes flimSound.h like so:

\code

errcode Bullet::SceneEntry()
{

	flimSound* bullet = new flimSound(SoundCallID::Explosion);
	bullet->Play();

}

\endcode


Properties of the sound can also be affected in this manner. See the flimSound.h documentation for more details. Parameters such as volume, pitch, and panning can
be tweened to different values over a set period of time or set instantly. 

For example:

\code

errcode Bullet::SceneEntry()
{

	flimSound* bullet = new flimSound(SoundCallID::Explosion);
	bullet->Play();

	// pans left speaker to right speaker over 1000 milliseconds
	bullet->Pan(-1.0f, 1.0f, 1000.0f);


	// volume is set to 0.5f instantly
	bullet->Volume(0.5f);


	// pitched is shifted from 0.1 to double speed over the course of 1000 milliseconds, and the operation will start in 2000 milliseconds
	bullet->Pitch(0.1f, 2.0f, 1000.0f, 2000.0f);

}

\endcode



*/


// REVERB!
/** \defgroup SOUNDREVERB Using Reverb
\ingroup SOUND
\brief How to access reverb properties of flimSounds

Similar to normal properties of the flimSound, each flimSound has a built-in reverb set to inactive by default.
This reverb can be activated by adjusting the volume in deciBels. The reverb supports the following adjustments:

\par Reverb Level: The level in deciBels (-80.0f to 20.0f) of the overall reverb send
\par Reverb Density: This sets the density of the space; 0 is like a church and 100.0f is like a silo (both reverberant, but shaped differently)
\par Reverb Predelay: This sets the time in milliseconds before the reverb begins after it receives a dry signal
\par Reverb time: This sets the time in milliseconds that the reverb will take to drop 60dB (longer reverb times make things more muddy)
\par Reverb Size: This sets the size of the space, 0 to 1000, and affects the diffusion of the reverb.

\code

errcode Level1::Initialize()
{
	music = new flimSound(SoundCallID::LevelMusic);
	music->Play(true);

	music->SetReverbLevel(-3.0f);
	music->SetReverbDensity(100.0f);
	music->SetReverbPreDelay(1000.0f);
	music->SetReverbSize(100.0f);
	music->SetReverbTime(100.0f);
}

\endcode


*/


// FILTERS!
/** \defgroup SOUNDFILTER Using Filters
\ingroup SOUND
\brief How to use flimFilters on flimSounds

You can also use flimFilter objects to add a low pass filter effect to sounds with a variable cutoff frequency.

\code

errcode Level1::Initialize()
{
	music = new flimSound(SoundCallID::LevelMusic);
	music->Play(true);
	
	flimFilter lpf;
	music->getFilter(lpf);
	lpf.SetCutoff(2000.0f);

}

\endcode

*/


// 3D SOUND
/** \defgroup SOUND3D Using 3D Sound and Occlusion
\ingroup SOUND
\brief How to activate the 3D sound engine

In a 3D Sound System, there are two key entities: the Listener and the Emitter. In flimEngine, there is one single listener for the scene (usually connected to the camera) and every 3D sound gets its own emitter.
Each must update its position and orientation every frame in order to be played back correctly, and 3D sounds are registered when the flimSound is created.

\code
errcode Tank::SceneEntry()
{

	// 3D sound set to true
	engineSound = new flimSound(SoundCallID::LevelMusic, true);
	engineSound->Play(true);

}


errcode Tank::Update()
{

	// set engine sound to the tank's position
	engineSound->SetPosition(this->position);

	//  set the Listener to the position of the camera
	FlimListener::SetPosition(camPosition);

	return errcode::success;
}

\endcode


In addition to positional audio, the sound can also register to be included in the occlusion system to have a low pass filter and volume attuenuation occur when a sound is behind a wall.

First, register flimSounds for collision in the Scene. Then any flimSound created with the occlusion tag will be registered for occlusion

\code
errcode Level1::Initialize()
{
	SetCollisionPair<flimSound, GameObject>();
}

errcode Tank::SceneEntry()
{

// 3D sound set to true, OCCLUSION registration set to true
engineSound = new flimSound(SoundCallID::LevelMusic, true, true);
engineSound->Play(true);

}

\endcode

*/

