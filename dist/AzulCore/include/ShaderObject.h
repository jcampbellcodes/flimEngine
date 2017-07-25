#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "sb6.h"

class ShaderObject
{
public:
	ShaderObject(const char * const shaderBaseFileName);
	void SetActive();
	GLint GetLocation(const char * uniformName);

private:
	bool privCreateShader(GLuint &programObject, const char * const shaderBaseFileName);
	bool privLoadNCompile(GLuint &shaderObject, const char * const shaderFileName, GLenum shader_type);

public:
	// data
	GLuint		programObject;
};

#endif