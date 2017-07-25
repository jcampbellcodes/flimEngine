#ifndef GRAPHICS_OBJECT_WIREFRAME_AUTOCOLOR_H
#define GRAPHICS_OBJECT_WIREFRAME_AUTOCOLOR_H

#include "GraphicsObject.h"

class GraphicsObject_WireframeAutoColor :public GraphicsObject
{
public:
	GraphicsObject_WireframeAutoColor(Model *model, ShaderObject *pShaderObj);

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;	
	virtual void privDraw() override;
	virtual void privRestoreState() override;

public:
// data:  place uniform instancing here
	GraphicsObject_WireframeAutoColor() = delete;


};
#endif