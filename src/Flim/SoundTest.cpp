#include "SoundTest.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "..\SceneDemo.h"
#include "..\FrigateFactory.h"
#include "..\SoundEngine\FlimListener.h"
#include "..\SoundEngine\flimSound.h"
#include "SceneManager.h"
#include "Scene.h"

SoundTest::SoundTest(std::string text, int _x, int _y, int _z, Scene* _scene) : scene(_scene)
{

	pGObj_Plane = new GraphicsObject_TextureFlat(&ModelManager::GetModel("Plane"), &ShaderManager::GetShader(text), &TextureManager::GetTexture("grid"));
	pGObj_Axis = new GraphicsObject_TextureFlat(&ModelManager::GetModel("Sphere"), &ShaderManager::GetShader(text), &TextureManager::GetTexture("Sphere"));


	//---------------------------------------------------------------------------------------------------------
	// Setup the current 3D perspective Camera
	//---------------------------------------------------------------------------------------------------------

	SceneManager::GetCurrentScene().GetCamera()->MainCamera().setViewport(0, 0, Flim::GetWidth(), Flim::GetHeight());
	SceneManager::GetCurrentScene().GetCamera()->MainCamera().setPerspective(35.0f, float(Flim::GetWidth()) / float(Flim::GetHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 10.0f, 20.0f);
	SceneManager::GetCurrentScene().GetCamera()->MainCamera().setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	SceneManager::GetCurrentScene().GetCamera()->MainCamera().updateCamera();

	// Camera vars
	CamPos = Vect(500, 100, 500);
	CamRot = Matrix(IDENTITY);		// No rotation initially
	CamUp = Vect(0, 1, 0);			// Using local Y axis as 'Up'
	CamDir = Vect(0, 0, 1);			// Using the local Z axis as 'forward'
	CamTranSpeed = 2;
	CamRotSpeed = .02f;
	Vect Target((float)_x, (float)_y, (float)_z);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);
	FlimListener::SetPosition(CamPos);




	// Creating matrices for in-world placement
	Matrix world;

	// Axis and Plane
	world = Matrix(SCALE, 20, 20, 20);
	pGObj_Axis->SetWorld(world);
	world = Matrix(SCALE, 400, 400, 400) * Matrix(TRANS, 0.0, -20.0f, 0.0f);
	pGObj_Plane->SetWorld(world);

	SubmitDrawRegistration();
	SubmitUpdateRegistration();
	SubmitInputRegistration(AZUL_KEY::KEY_Q, input_type::pressed);
	SubmitInputRegistration(AZUL_KEY::KEY_C, input_type::pressed);

	this->music = new flimSound(SoundCallID::GarageMusic, true, true);
	music->Play(true);
	music->Volume(1.0f);
	music->setPosition(world.get(MatrixRowType::ROW_3));


	music->SetReverbLevel(-6.0f);
	music->SetReverbPreset(flimReverb::PLATE);



}

SoundTest::~SoundTest()
{
	SubmitDrawDeregistration();
	SubmitInputDeregistration(AZUL_KEY::KEY_Q, input_type::pressed);
	music->Stop();
	delete music;
	DebugMsg::out("World Cleaned\n");
}

errcode SoundTest::KeyPressed(AZUL_KEY key)
{

	// make three random numbers
	// make a new frigate
	if (key == AZUL_KEY::KEY_Q)
	{
		SceneManager::ChangeScene(scene);
	}

	return errcode::success;
}

errcode SoundTest::Draw()
{
	// draw all objects
	pGObj_Plane->Render(&SceneManager::GetCurrentScene().GetCamera()->MainCamera());
	pGObj_Axis->Render(&SceneManager::GetCurrentScene().GetCamera()->MainCamera());
	return errcode::success;
}

errcode SoundTest::Update()
{

	//SceneManager::GetCurrentScene().GetCamera()->MainCamera().setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	//SceneManager::GetCurrentScene().GetCamera()->MainCamera().updateCamera();



	// Camera translation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
	{
		CamPos += Vect(0, 0, 1) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
	{
		CamPos += Vect(0, 0, 1) * CamRot * -CamTranSpeed;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
	{
		CamPos += Vect(1, 0, 0) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
	{
		CamPos += Vect(1, 0, 0) * CamRot * -CamTranSpeed;
	}

	// Camera Rotation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		CamRot *= Matrix(ROT_Y, CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		CamRot *= Matrix(ROT_Y, -CamRotSpeed);
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, -CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, CamRotSpeed);
	}

	// Update the camera settings
	SceneManager::GetCurrentScene().GetCamera()->MainCamera().setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	SceneManager::GetCurrentScene().GetCamera()->MainCamera().updateCamera();

	SceneManager::Get2DCamera().updateCamera();


	Vect outUp;
	Vect outForward;
	Vect outPos;
	SceneManager::GetCurrentScene().GetCamera()->MainCamera().getUp(outUp);
	//SceneManager::GetCurrentScene().GetCamera()->MainCamera().getLookAt(outForward);
	SceneManager::GetCurrentScene().GetCamera()->MainCamera().getDir(outForward);
	SceneManager::GetCurrentScene().GetCamera()->MainCamera().getPos(outPos);

	//DebugMsg::out("%f, %f, %f\n", outForward.X(), outForward.Y(), outForward.Z());

	// Axis and Plane
	Matrix world = Matrix(SCALE, 20, 20, 20);
	pGObj_Axis->SetWorld(world);
	//world = Matrix(SCALE, 400, 400, 400) * Matrix(TRANS, 0.0, -20.0f, 0.0f);
	FlimListener::SetPosition(outPos);
	FlimListener::SetOrientation(outForward, outUp);
	music->setPosition(Vect(0,0,0));


	//DebugMsg::out("Campos: %f,%f,%f.       EmitterPos:%f, %f, %f \n\n\n ", CamPos.X(), CamPos.Y(), CamPos.Z(), world.get(MatrixRowType::ROW_3).X(), world.get(MatrixRowType::ROW_3).Y(), world.get(MatrixRowType::ROW_3).Z());


	return errcode::success;
}