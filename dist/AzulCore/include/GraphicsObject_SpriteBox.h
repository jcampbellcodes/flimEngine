#ifndef GRAPHICS_OBJECT_BOX_H
#define GRAPHICS_OBJECT_BOX_H

#include <sb6.h>
#include "MathEngine.h"
#include "GraphicsObject.h"
#include "Rect.h"

class GraphicsObject_SpriteBox : public GraphicsObject
{
public:
	GraphicsObject_SpriteBox(Model *model, ShaderObject *pShaderObj, Rect *pRect, Vect &Color);

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;
	virtual void privDraw() override;
	virtual void privRestoreState() override;

public:
	// data:  place uniform instancing here
	Matrix  *pMatrix_orig;
	Vect	*pColor;
	float origWidth;
	float origHeight;

	float origPosX;
	float origPosY;
};
#endif