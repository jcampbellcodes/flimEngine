#ifndef GRAPHICS_OBJECT_TEXTURE_FLAT_H
#define GRAPHICS_OBJECT_TEXTURE_FLAT_H

#include <sb6.h>
#include "GraphicsObject.h"
#include "Texture.h"

class GraphicsObject_TextureFlat : public GraphicsObject
{
public:
	// Default parameters with references are non-conventional, opted for overloading technique
	GraphicsObject_TextureFlat(Model *model, ShaderObject *pShaderObj, Texture *pTex);
	GraphicsObject_TextureFlat(Model *model, ShaderObject *pShaderObj, Texture *pTex, Texture *pTex2);
	GraphicsObject_TextureFlat(Model *model, ShaderObject *pShaderObj, Texture *pTex, Texture *pTex2, Texture *pTex3);
	GraphicsObject_TextureFlat(Model *model, ShaderObject *pShaderObj, Texture *pTex, Texture *pTex2, Texture *pTex3, Texture *pTex4);

protected:
	// Rendermaterial contract
	virtual void privSetState() override;
	virtual void privSetDataGPU( Camera *pCam ) override;	
	virtual void privDraw() override;
	virtual void privRestoreState() override;

public:
// data:  place uniform instancing here
	GLuint textureID;
	GLuint textureID2;
	GLuint textureID3;
	GLuint textureID4;


	GraphicsObject_TextureFlat() = delete;

};
#endif