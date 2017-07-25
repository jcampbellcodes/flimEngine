#pragma once
#pragma once
#ifndef SCENECMD_H
#define SCENECMD_H

#include "Command.h"

class Scene;

class SceneCommand : public Command
{
public:
	// big four
	SceneCommand() = delete;
	SceneCommand(const SceneCommand&) = default;
	~SceneCommand() = default;
	SceneCommand& operator=(const SceneCommand&) = default;

	SceneCommand(Scene* _scene);

	void execute() override;

private:
	Scene* scene;

};

#endif