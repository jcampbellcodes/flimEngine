#ifndef GRAPHICS_OBJECT_TEXTURE_LIGHT_H
#define GRAPHICS_OBJECT_TEXTURE_LIGHT_H

#include "GraphicsObject.h"
#include "Texture.h"

class GraphicsObject_TextureLight :public GraphicsObject
{
public:
	// Default parameters with pointers in middle of arg list are non-conventional, opted for overloading technique
	GraphicsObject_TextureLight(Model *model, ShaderObject *pShaderObj, Texture *pTex, Vect &LightColor, Vect &LightPos);
	GraphicsObject_TextureLight(Model *model, ShaderObject *pShaderObj, Texture *pTex, Texture *pTex2, Vect &LightColor, Vect &LightPos);
	GraphicsObject_TextureLight(Model *model, ShaderObject *pShaderObj, Texture *pTex, Texture *pTex2, Texture *pTex3,Vect &LightColor, Vect &LightPos);
	GraphicsObject_TextureLight(Model *model, ShaderObject *pShaderObj, Texture *pTex, Texture *pTex2, Texture *pTex3, Texture *pTex4, Vect &LightColor, Vect &LightPos);


	~GraphicsObject_TextureLight();

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

	Vect *pLightColor;
	Vect *pLightPos;

	GraphicsObject_TextureLight() = delete;
};
#endif