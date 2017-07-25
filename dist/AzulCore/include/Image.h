#ifndef IMAGE_H
#define IMAGE_H

#include "Rect.h"
#include "Texture.h"

class Image
{    
public:
	// public methods: -------------------------------------------------------------
	Image();
	Image(Texture *pTexture, Rect *pRect);
	void Set(Texture *pTexture, Rect *pRect);
	~Image();

public:
	// data: -----------------------------------------------------------------------
	Rect		*pImageRect;
	Texture		*pText;
};


#endif