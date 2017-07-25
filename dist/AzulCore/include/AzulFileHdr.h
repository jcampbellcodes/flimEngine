#ifndef AZUL_FILE_HDR_H
#define AZUL_FILE_HDR_H

#include <string.h>
#include "MathEngine.h"

#define OBJECT_NAME_SIZE   32

struct AzulFileHdr
{   
	AzulFileHdr()
	{
		memset( this, 0x0, sizeof(AzulFileHdr) );
	}

	~AzulFileHdr()
	{
		// do nothing
	}

	// object name
	char	objName[ OBJECT_NAME_SIZE ];
   
	// vertex buffer
		int	numVerts;
		int	vertBufferOffset;
   
	// trilist index 
		int	numTriangles;
		int	triangleListBufferOffset;

	// texture names
		int  numTextures;
		int  textureNamesOffset;  // zero terminated list, strings sequentially stored
		int  textureNamesInBytes;

	// Bounding Sphere: bounding volume
		Vect center;
		float radius;

	// AABB: axis aligned bounding box
		// Specifies the minimum extent of this AABB in the world space x, y and z axes.
		Vect minPointAABB;
		// Specifies the maximum extent of this AABB in the world space x, y and z axes
		Vect maxPointAABB;

/* ------------------------------------------------------
 DataLayout:  // sample
	   char   objName[ OBJECT_NAME_SIZE ];
	   int    numVerts;
	   int    vertBufferOffset;
	   int    numTriangles;
	   int    triangleListBufferOffset;
	   int    numTextures;
	   int    textureNamesOffset; 
	   Vect   center;
	   float  radius;
	   Vect   minPointAABB;
	   Vect   maxPointAABB;
 TextureNames: // sample: numTextures=2
    "TextureName0.tga"
	"TextureNameLengthDoesntMatter1.tga"
 Verts:  // sample: numVerts=5, type VertexStride_VUN ={x,y,z,u,v,nx,ny,nz}
	4.5f, 3.4f, 3.4f, 0.4f, 0.3f, 0.2f, 0.4f, 0.2f
	2.5f, -3.4f, 3.4f, 0.6f, 0.3f, -0.4f, -0.4f, 0.2f
	1.5f, 1.4f, -2.4f, 0.4f, 0.63f, 0.3f, -0.4f, -0.2f
	-4.5f, 3.4f, 1.4f, 0.2f, 0.3f, 0.1f, -0.4f, 0.2f
	9.5f, -2.4f, -3.4f, 0.2f, 0.5f, -0.6f, 0.4f, 0.2f
 Tris:  // samble: numTriangles=3, type TriangleIndex={v0,v1,v2}
    0, 1, 2
	2, 3, 0
    4, 1, 2
    
 ------------------------------------------------------- */
};

#endif