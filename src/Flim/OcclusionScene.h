#pragma once
#ifndef OcclusionScene_H
#define OcclusionScene_H

#include "Scene.h"

#include "..\Frigate.h"
#include "SoundTest.h"
#include "..\Cottage.h"
#include "..\Enemy.h"

class OcclusionScene : public Scene
{
public:
	OcclusionScene() = default;
	OcclusionScene(const OcclusionScene&) = default;
	virtual ~OcclusionScene() override;
	const OcclusionScene& operator=(const OcclusionScene&) = delete;

	errcode Initialize() override;
	errcode Terminate() override;

private:
	Frigate* frigate;
	SoundTest* worldPlane;
	Cottage* cottage;


	errcode err;

};

#endif // !OcclusionScene_H
