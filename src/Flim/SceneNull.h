#pragma once
#ifndef SceneNull_H
#define SceneNull_H

#include "Scene.h"

// null obj pattern

class SceneNull : public Scene
{
public: 
	SceneNull() = default;
	SceneNull(const SceneNull&) = default;
	virtual ~SceneNull() {
		//DebugMsg::out("scene null destroyed\n");
	};
	const SceneNull& operator=(const SceneNull&) = delete;

	errcode Initialize() override { return errcode::success; };
	errcode Terminate() override { return errcode::success; };

};

#endif // !SceneNull_H
