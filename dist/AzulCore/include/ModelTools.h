// ModelTools
// Support tools to compute bounding volumes on models
// Ported/adapted from Keenan's FBX Converter code
// Andre Berthiaume, June 2016

#ifndef _ModelTools
#define _ModelTools

#include "Vect.h"

struct VertexStride_VUN;
struct TriangleIndex;

class ModelTools
{
public: 
	struct Sphere
	{
		Vect cntr;
		float rad;
	};

	struct AABB
	{
		// Specifies the minimum extent of this AABB in the world space x, y and z axes.
		Vect minPointAABB;
		// Specifies the maximum extent of this AABB in the world space x, y and z axes
		Vect maxPointAABB;
	};

private:
	static void SphereFromDistantPoints(Sphere &s, VertexStride_VUN *pt, int numPts);
	static void MostSeparatedPointsOnAABB(int &min, int &max, VertexStride_VUN *pt, int numPts);
	static void SphereFromSphereAndPt(Sphere &s, VertexStride_VUN &p);

public:
	static void ComputeRitterSphere(Sphere &s, VertexStride_VUN *pt, int numPts);
	static void ComputeAxisAlignedBox(AABB &b, VertexStride_VUN *pt, int numPts);

	static void CreateUnitSquareXY(VertexStride_VUN *&pVerts, int& nverts, TriangleIndex *&pTriList, int& ntri);
	static void CreateUnitBox(VertexStride_VUN *&pVerts, int& nverts, TriangleIndex *&pTriList, int& ntri);
	static void CreateUnitSphere(int vslice, int hslice, VertexStride_VUN *&pVerts, int& nverts, TriangleIndex *&pTriList, int& ntri);


};



#endif _ModelTools