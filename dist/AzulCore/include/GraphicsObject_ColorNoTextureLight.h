#ifndef GRAPHICS_OBJECT_COLOR_NO_TEXTURE_LIGHT_H
#define GRAPHICS_OBJECT_COLOR_NO_TEXTURE_LIGHT_H

#include "GraphicsObject.h"


class GraphicsObject_ColorNoTextureLight :public GraphicsObject
{
public:
	GraphicsObject_ColorNoTextureLight(Model *model, ShaderObject *pShaderObj, Vect &LightColor, Vect &LightPos);
	~GraphicsObject_ColorNoTextureLight();

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;	
	virtual void privDraw() override;
	virtual void privRestoreState() override;

public:
// data:  place uniform instancing here
	Vect *pLightColor;
	Vect *pLightPos;

	GraphicsObject_ColorNoTextureLight() = delete;

};
#endif