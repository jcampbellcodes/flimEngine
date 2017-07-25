#ifndef TEXTURE_H
#define TEXTURE_H

#include "sb6.h"

#define TEXTURE_ASSET_NAME_SIZE 64

class Texture
{
public:
	Texture();
	~Texture();
		
	// Load from file _assetName
	Texture(const char * const _assetName);

	// Load directly from array 0f GLbyte
	Texture(GLbyte* pixArray, int width, int height, int filtermode = GL_LINEAR);

	// Single pixel texture
	Texture(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255);


private:
	GLuint textureID;
	GLenum minFilter;
	GLenum magFilter;
	GLenum wrapMode;
	int textureWidth;
	int textureHeight;

	void set(const char * const _assetName,
		GLuint _TextureID,
		GLenum minFilter,
		GLenum magFilter,
		GLenum wrapMode,
		int width,
		int height);

	char assetName[TEXTURE_ASSET_NAME_SIZE];

	bool privLoadTexture(GLbyte* pixArray, int nComponents, GLenum eFormat, GLenum minFilter, GLenum magFilter, GLenum wrapMode, int &width, int &height);

	void DefaultTexturePixelarray(GLbyte*& pixels, GLenum& minFilter, GLenum& magFilter,  int &width, int &height);

public:
	int getWidth()
	{ 
		return this->textureWidth; 
	};
	int getHeight()
	{ 
		return this->textureHeight;  
	};
	GLuint getTextureID()
	{ 
		return textureID; 
	}
	const char* getName()
	{ 
		return assetName; 
	}
	
	static GLbyte UChartoGLbyte(unsigned char c);
};


#endif