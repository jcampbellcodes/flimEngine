#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "Camera.h"
#include "Model.h"

class RenderMaterial
{
protected:
	virtual void privSetState() = 0;
	virtual void privSetDataGPU( Camera *pCam ) = 0;	
	virtual void privDraw() = 0;
	virtual void privRestoreState() = 0;
};

class GraphicsObject: protected RenderMaterial
{
public:
	GraphicsObject(Model *model, ShaderObject *pShaderObj);
	virtual ~GraphicsObject();

	GraphicsObject() = delete;

	void Render( Camera *pCam );
	void SetWorld( Matrix &_world);

	Model *getModel() const;
	Matrix &getWorld();

protected:
	Model			*pModel;
	Matrix			*pWorld;
	ShaderObject	*pShaderObj;
};

#endif