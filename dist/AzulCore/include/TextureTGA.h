#ifndef TEXTURE_TGA_H
#define TEXTURE_TGA_H

GLbyte *gltReadTGABits(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

void FlipYAxis(GLbyte* img, GLint width, GLint height, size_t bpp);

#endif