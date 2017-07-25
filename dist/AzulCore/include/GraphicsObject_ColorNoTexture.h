#ifndef GRAPHICS_OBJECT_COLOR_NO_TEXTURE_H
#define GRAPHICS_OBJECT_COLOR_NO_TEXTURE_H

#include "GraphicsObject.h"

class GraphicsObject_ColorNoTexture :public GraphicsObject
{
public:
	GraphicsObject_ColorNoTexture(Model *model, ShaderObject *pShaderObj);

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;	
	virtual void privDraw() override;
	virtual void privRestoreState() override;

public:
// data:  place uniform instancing here
	GraphicsObject_ColorNoTexture() = delete;

};
#endif