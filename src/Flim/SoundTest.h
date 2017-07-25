#pragma once
#pragma once
#ifndef SoundTest_H
#define SoundTest_H

#include "AzulCore.h"
#include "Align16.h"
#include "GameObject.h"
#include "Scene.h"

#include "Terrain.h"
class flimSound;

class SoundTest : public GameObject
{
private:
	GraphicsObject_TextureFlat* pGObj_Plane;
	GraphicsObject_TextureFlat* pGObj_Axis;
	GraphicsObject_TextureLight* terrainGO;
	GraphicsObject_WireframeConstantColor* terrainGOWire;

	flimSound* music;

public:
	SoundTest() = delete;
	SoundTest(std::string text, int _x, int _y, int _z, Scene* _scene);
	SoundTest(const SoundTest&) = default;
	~SoundTest();
	const SoundTest& operator=(const SoundTest&) {};

	errcode KeyPressed(AZUL_KEY key) override;

	virtual errcode Draw() override;
	virtual errcode Update() override;

	// Camera vars
	Vect CamPos;
	Matrix CamRot;		// No rotation initially
	Vect CamUp;			// Using local Y axis as 'Up'
	Vect CamDir;			// Using the local Z axis as 'forward'
	float CamTranSpeed;
	float CamRotSpeed;

	FlimTerrain* terrain;

	Scene* scene;

};

#endif // !SoundTest_H
