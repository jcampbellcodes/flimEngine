#pragma once
#ifndef SCENECHANGECMD_H
#define SCENECHANGECMD_H

#include "Command.h"

class Scene;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SceneChangeCommand
///
/// \brief	Replaces scene update command in SceneManager update and tells scene to change
///
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class SceneChangeCommand : public Command
{
public:
	// big four
	SceneChangeCommand() = delete;
	SceneChangeCommand(const SceneChangeCommand&) = default;
	~SceneChangeCommand() = default;
	SceneChangeCommand& operator=(const SceneChangeCommand&) = default;


	SceneChangeCommand(Scene* _scene);

	void execute() override;

private:
	Scene* scene;

};

#endif