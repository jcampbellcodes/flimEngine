#pragma once
#ifndef SCENEUpdateCMD_H
#define SCENEUpdateCMD_H

#include "Command.h"

class Scene;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	SceneUpdateCommand
///
/// \brief	Tells scene manager to continue business as usual -- switched out with a scene change command later
///
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class SceneUpdateCommand : public Command
{
public:
	// big four
	SceneUpdateCommand();
	SceneUpdateCommand(const SceneUpdateCommand&) = default;
	~SceneUpdateCommand() = default;
	SceneUpdateCommand& operator=(const SceneUpdateCommand&) = default;

	//SceneUpdateCommand(Scene* _scene);

	void execute() override;

private:

};

#endif