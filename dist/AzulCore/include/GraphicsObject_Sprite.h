#ifndef GRAPHICS_OBJECT_SPRITE_H
#define GRAPHICS_OBJECT_SPRITE_H

#include <sb6.h>
#include "GraphicsObject.h"
#include "Texture.h"
#include "Image.h"

class GraphicsObject_Sprite : public GraphicsObject
{
public:
	GraphicsObject_Sprite(Model *model, ShaderObject *pShaderObj, Image *image, Rect *rect);

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;	
	virtual void privDraw() override;
	virtual void privRestoreState() override;

public:
// data:  place uniform instancing here
	
	//GLuint textureID;
	Image	*pImage;
	Matrix	*pMatrix_uv;
	Matrix  *pMatrix_orig;

	float origWidth; 
	float origHeight; 

	float origPosX;
	float origPosY;
};
#endif