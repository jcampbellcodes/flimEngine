#include "Terrain.h"
#include "GpuVertTypes.h"
#include "AzulCore.h"
#include "Texture.h"
#include "Model.h"
#include "TextureTGA.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "Visualizer.h"

FlimTerrain::FlimTerrain(const char* heightmapFile, const char* texturePath = "grid", float _sideLength = 100.0f, float _maxHeight = 10.0f, float _zeroAltitude = 0.0f, float U = 30.0f, float V = 30.0f) 
	: terrainSideLength(_sideLength), maxHeight(_maxHeight), zeroAltitutde(_zeroAltitude)
{
	// load in RGB
	int icomp;
	unsigned int dtype;
	std::string path = "Heightmaps\\" + std::string(heightmapFile);
	imgData = gltReadTGABits(path.c_str(), &imgWidth, &imgHeight, &icomp, &dtype);
	assert(imgData);
	assert(imgWidth == imgHeight && imgWidth != 0); // We need square images for heightmaps

	NUM_VERTS = (imgWidth * imgHeight);
	NUM_TRIS = 2 * ((imgWidth - 1) * (imgHeight- 1));
	

	
	// fill verts
	this->pVerts = new VertexStride_VUN[NUM_VERTS];
	this->tlist = new TriangleIndex[NUM_TRIS];
	cellDimension = _sideLength / imgWidth;
	pixel_width = 3; // BEWARE! switch to 3 if your heights are a repeated spiky pattern/ messed up. TODO -- determine whether data is RGB or RGBA
	float y = zeroAltitutde;
	float fltTemp = 1.0f;

	// fill vertex array
	for (int i = 0; i < imgWidth; i++) // rows
	{
		for (int j = 0; j < imgHeight; j++) // columns
		{

			y = PixelToFloat(
				imgData[PixelIndex(i,j)]
			);

			pVerts[VertexIndex(i,j)].set(j * cellDimension, y, i * cellDimension, (fltTemp * i * U / imgHeight), (fltTemp * j * V / imgHeight), 0.0f, 1.0f, 0.0f);
		}
	}


	
	int v = 0;
	for (int t = 0; t < NUM_TRIS; t+=2) // rows
	{
		if ((v + 1) % imgHeight == 0)
		{
			v++;
		}

		//counter clockwise
		this->tlist[t].set(v + 1, v,  v + imgHeight);
		this->tlist[t + 1].set(v + 1, v + imgHeight, v + imgHeight + 1);


		v++;
	}
	

	this->terrainModel = new Model(pVerts, NUM_VERTS, tlist, NUM_TRIS);

	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(100.0f, 1000.0f, 1000.0f, 1.0f);
	terrainGO = new GraphicsObject_TextureLight(terrainModel, &ShaderManager::GetShader("__FLIM__textureLightRender"), &TextureManager::GetTexture(texturePath), LightColor, LightPos);
	//terrainGO = new GraphicsObject_TextureFlat(terrainModel, &ShaderManager::GetShader("__FLIM__textureFlatRender"), &TextureManager::GetTexture(texturePath));
	Vect col(flimColor::darkGray);
	terrainGOWire = new GraphicsObject_WireframeConstantColor(terrainModel, &ShaderManager::GetShader("__FLIM__colorConstantRender"), col);




}

errcode FlimTerrain::ActivateTerrain()
{
	//SubmitDrawRegistration();
	return errcode::success;
}

errcode FlimTerrain::DeactivateTerrain()
{
	//SubmitDrawDeregistration();
	return errcode::success;
}

FlimTerrain::~FlimTerrain()
{
}

errcode FlimTerrain::Draw()
{
	terrainGO->Render(&SceneManager::GetCurrentScene().GetCamera()->MainCamera());
	//terrainGOWire->Render(&SceneManager::GetCurrentScene().GetCamera()->MainCamera());

	return errcode::success;
}

int FlimTerrain::VertexIndex(int i, int j)
{
	return (i*(imgHeight)+j);
}

int FlimTerrain::PixelIndex(int i, int j)
{
	return pixel_width * (j*imgHeight + i);
}

float FlimTerrain::PixelToFloat(unsigned char hval)
{
	return (hval / 255.0f) * maxHeight;
}

int FlimTerrain::TriIndex(int i, int j)
{
	return ((imgWidth - 1) / 2) * i +(2*(imgHeight - 1) * j);
}

void FlimTerrain::ShowCells()
{
	// fill vertex array
	Vect min;
	Vect max;
	for (int i = 0; i < imgWidth - 1; i++) // rows
	{
		for (int j = 0; j < imgHeight - 1; j++) // columns
		{
			if (FindMin(i, j, min) == errcode::success && FindMax(i, j, max) == errcode::success)
			{
 				Visualizer::ShowAABB(min, max, flimColor::red);
			}
		}
	}
}

errcode FlimTerrain::FindMax(int i, int j, Vect& out)
{
	if (!(i < imgHeight - 1 && j < imgHeight - 1))
	{
		return errcode::failure;
	}

	
	Vect NW(pVerts[VertexIndex(i, j)].x, pVerts[VertexIndex(i, j)].y, pVerts[VertexIndex(i, j)].z);
	Vect NE(pVerts[VertexIndex(i + 1, j)].x, pVerts[VertexIndex(i + 1, j)].y, pVerts[VertexIndex(i + 1, j)].z);
	Vect SW(pVerts[VertexIndex(i, j + 1)].x, pVerts[VertexIndex(i, j + 1)].y, pVerts[VertexIndex(i, j + 1)].z);
	Vect SE(pVerts[VertexIndex(i + 1, j + 1)].x, pVerts[VertexIndex(i + 1, j + 1)].y, pVerts[VertexIndex(i + 1, j + 1)].z);

	Vect Max(NW);

	FlimMath::getMaxComponent(Max, NW);
	FlimMath::getMaxComponent(Max, NE);
	FlimMath::getMaxComponent(Max, SW);
	FlimMath::getMaxComponent(Max, SE);

	out = Max;
	return errcode::success;
}

errcode FlimTerrain::FindMin(int i, int j, Vect& out)
{
	if (!(i < imgHeight - 1 && j < imgHeight - 1))
	{
		return errcode::failure;
	}

	Vect NW(pVerts[VertexIndex(i, j)].x, pVerts[VertexIndex(i, j)].y, pVerts[VertexIndex(i, j)].z);
	Vect NE(pVerts[VertexIndex(i + 1, j)].x, pVerts[VertexIndex(i + 1, j)].y, pVerts[VertexIndex(i + 1, j)].z);
	Vect SW(pVerts[VertexIndex(i, j + 1)].x, pVerts[VertexIndex(i, j + 1)].y, pVerts[VertexIndex(i, j + 1)].z);
	Vect SE(pVerts[VertexIndex(i + 1, j + 1)].x, pVerts[VertexIndex(i + 1, j + 1)].y, pVerts[VertexIndex(i + 1, j + 1)].z);

	Vect Min(NW);

	FlimMath::getMinComponent(Min, NW);
	FlimMath::getMinComponent(Min, NE);
	FlimMath::getMinComponent(Min, SW);
	FlimMath::getMinComponent(Min, SE);

	out = Min;
	return errcode::success;
}

errcode FlimTerrain::ShowNearestCell(const Vect & pos)
{
	int i = int(pos.Z() / cellDimension);
	int j = int(pos.X() / cellDimension);
	Vect min, max;
	if (FindMin(i, j, min) == errcode::success && FindMax(i, j, max) == errcode::success)
	{
		Visualizer::ShowAABB(min, max, flimColor::red);
	}
	else
	{
		return errcode::failure;
	}

	return errcode::success;
}

CollisionVolumeAABB FlimTerrain::FindNearestCell(const Vect & pos)
{
	CollisionVolumeAABB aabb = CollisionVolumeAABB();
	int i = int(pos.Z() / cellDimension);
	int j = int(pos.X() / cellDimension);
	Vect min, max;
	if (FindMin(i, j, min) == errcode::success && FindMax(i, j, max) == errcode::success)
	{
		aabb.SetMinMax(min, max);
		
	}
	return aabb;
}

errcode FlimTerrain::ShowExactPosition(const Vect & pos)
{
	//1: find cell
	int i = int(pos.Z() / cellDimension);
	int j = int(pos.X() / cellDimension);
	if (i >= imgHeight || j >= imgHeight)
	{
		return errcode::failure;
	}

	//2: determine which triangle in cell -- compare Vertex(i,j) - pos and Vertex(i+1, j+1) - pos
	Vect NW(pVerts[VertexIndex(i, j)].x, pVerts[VertexIndex(i, j)].y, pVerts[VertexIndex(i, j)].z);
	//Visualizer::ShowMarker(NW, flimColor::yellow);
	Vect SE(pVerts[VertexIndex(i + 1, j + 1)].x, pVerts[VertexIndex(i + 1, j + 1)].y, pVerts[VertexIndex(i + 1, j + 1)].z);
	//Visualizer::ShowMarker(SE, flimColor::yellow);

	Visualizer::ShowLine(NW, pos);
	Visualizer::ShowLine(SE, pos);

	//TriangleIndex triangle;

	Vect a, b, c;

	if ((NW - pos).magSqr() < (SE - pos).magSqr()) // use NW as 'a'
	{
		//triangle = tlist[TriIndex(i, j)]; // first triangle of pair

		a = NW;
		b = Vect(pVerts[VertexIndex(i, j + 1)].x, pVerts[VertexIndex(i, j + 1)].y, pVerts[VertexIndex(i, j + 1)].z);
		c = Vect(pVerts[VertexIndex(i + 1, j)].x, pVerts[VertexIndex(i + 1, j)].y, pVerts[VertexIndex(i + 1, j)].z);

	}
	else // use SE as 'a'
	{
		//triangle = tlist[TriIndex(i, j) + 1]; // second triangle of pair

		a = SE;
		b = Vect(pVerts[VertexIndex(i + 1, j)].x, pVerts[VertexIndex(i + 1, j)].y, pVerts[VertexIndex(i + 1, j)].z);
		c = Vect(pVerts[VertexIndex(i, j + 1)].x, pVerts[VertexIndex(i, j + 1)].y, pVerts[VertexIndex(i, j + 1)].z);

	}

	//3: make line plane intersection with three vertices that make up chosen triangle
	// -- define plane from three points
	//  a - b => AB, c - b => CB
	//  normal => AB.cross(CB)
	//  plane eqn is :     d = normalX*(a.x) + normalY*(a.y) + normalZ*(a.z)
	//  t = -(pos.dot(normal) + d) / (downVector.dot(normal)
	//  P = pos + t*(downVector)

	//Vect a(pVerts[triangle.v0].x, pVerts[triangle.v0].y, pVerts[triangle.v0].z);
	//Vect b(pVerts[triangle.v1].x, pVerts[triangle.v1].y, pVerts[triangle.v1].z);
	//Vect c(pVerts[triangle.v2].x, pVerts[triangle.v2].y, pVerts[triangle.v2].z);

	Visualizer::ShowLine(a, b, flimColor::green);
	Visualizer::ShowLine(c, b, flimColor::green);
	Visualizer::ShowLine(c, a, flimColor::green);

	Visualizer::ShowMarker(a, flimColor::green);
	Visualizer::ShowMarker(b, flimColor::green);
	Visualizer::ShowMarker(c, flimColor::green);

	Vect AB = b - a;
	Vect CB = c - a;
	Vect normal = AB.cross(CB);



	/*
	Vect normal = Vect(
	AB.Y()*CB.Z() - AB.Z()*CB.Y(),
	AB.Z()*CB.X() - AB.X()*CB.Z(),
	AB.X()*CB.Y() - AB.Y()*CB.X()
	);
	normal.norm();
	*/

	// d is direction of the ray --> straight down
	Vect d(0, -1.0f, 0);
	// pos is origin of the ray
	// n is normal

	float t = -((pos - a).dot(normal) / d.dot(normal));

	//float d = (normal.X() * a.X()) + (normal.Y() * a.Y()) + (normal.Z() * a.Z());
	//float t = -(pos.dot(normal) + d) / (Vect(0, 1, 0).dot(normal));


	Vect P(pos + t*d);
	Visualizer::ShowLine(pos, P);
	//4: show a marker at this point

	Visualizer::ShowMarker(P, flimColor::red);

	return errcode::success;
}

Vect FlimTerrain::GetNormalizedPosition(const Vect& pos)
{
	//1: find cell
	float i = pos.Z() / cellDimension;
	float j = pos.X() / cellDimension;

	return Vect(j, i, 0);
}


errcode FlimTerrain::GetExactPosition(const Vect & pos, Vect& output)
{
	//1: find cell
	int i = int(pos.Z() / cellDimension);
	int j = int(pos.X() / cellDimension);
	if ((i >= imgHeight || j >= imgHeight || i + 1 >= imgHeight || j + 1 >= imgHeight))
	{
		return errcode::no_terrain;
		//return errcode::failure;
	}

	//2: determine which triangle in cell -- compare Vertex(i,j) - pos and Vertex(i+1, j+1) - pos
 	Vect NW(pVerts[VertexIndex(i, j)].x, pVerts[VertexIndex(i, j)].y, pVerts[VertexIndex(i, j)].z);
	//Visualizer::ShowMarker(NW, flimColor::yellow);
	Vect SE(pVerts[VertexIndex(i + 1, j + 1)].x, pVerts[VertexIndex(i + 1, j + 1)].y, pVerts[VertexIndex(i + 1, j + 1)].z);
	//Visualizer::ShowMarker(SE, flimColor::yellow);

	//Visualizer::ShowLine(NW, pos);
	//Visualizer::ShowLine(SE, pos);

	//TriangleIndex triangle;

	Vect a, b, c;

	if ((NW - pos).magSqr() < (SE - pos).magSqr()) // use NW as 'a'
	{
		//triangle = tlist[TriIndex(i, j)]; // first triangle of pair

		a = NW;
		b = Vect(pVerts[VertexIndex(i, j + 1)].x, pVerts[VertexIndex(i, j + 1)].y, pVerts[VertexIndex(i, j + 1)].z);
		c = Vect(pVerts[VertexIndex(i + 1, j)].x, pVerts[VertexIndex(i + 1, j)].y, pVerts[VertexIndex(i + 1, j)].z);

	}
	else // use SE as 'a'
	{
		//triangle = tlist[TriIndex(i, j) + 1]; // second triangle of pair

		a = SE;
		b = Vect(pVerts[VertexIndex(i + 1, j)].x, pVerts[VertexIndex(i + 1, j)].y, pVerts[VertexIndex(i + 1, j)].z);
		c = Vect(pVerts[VertexIndex(i, j + 1)].x, pVerts[VertexIndex(i, j + 1)].y, pVerts[VertexIndex(i, j + 1)].z);

	}

	//3: make line plane intersection with three vertices that make up chosen triangle
	// -- define plane from three points
	//  a - b => AB, c - b => CB
	//  normal => AB.cross(CB)
	//  plane eqn is :     d = normalX*(a.x) + normalY*(a.y) + normalZ*(a.z)
	//  t = -(pos.dot(normal) + d) / (downVector.dot(normal)
	//  P = pos + t*(downVector)

	//Vect a(pVerts[triangle.v0].x, pVerts[triangle.v0].y, pVerts[triangle.v0].z);
	//Vect b(pVerts[triangle.v1].x, pVerts[triangle.v1].y, pVerts[triangle.v1].z);
	//Vect c(pVerts[triangle.v2].x, pVerts[triangle.v2].y, pVerts[triangle.v2].z);

	//Visualizer::ShowLine(a, b, flimColor::green);
	//Visualizer::ShowLine(c, b, flimColor::green);
	//Visualizer::ShowLine(c, a, flimColor::green);

	//Visualizer::ShowMarker(a, flimColor::green);
	//Visualizer::ShowMarker(b, flimColor::green);
	//Visualizer::ShowMarker(c, flimColor::green);

	Vect AB = b - a;
	Vect CB = c - a;
	Vect normal = AB.cross(CB);



	/*
	Vect normal = Vect(
	AB.Y()*CB.Z() - AB.Z()*CB.Y(),
	AB.Z()*CB.X() - AB.X()*CB.Z(),
	AB.X()*CB.Y() - AB.Y()*CB.X()
	);
	normal.norm();
	*/

	// d is direction of the ray --> straight down
	Vect d(0, -1.0f, 0);
	// pos is origin of the ray
	// n is normal

	float t = -((pos - a).dot(normal) / d.dot(normal));

	//float d = (normal.X() * a.X()) + (normal.Y() * a.Y()) + (normal.Z() * a.Z());
	//float t = -(pos.dot(normal) + d) / (Vect(0, 1, 0).dot(normal));


	Vect P(pos + t*d);
	//Visualizer::ShowLine(pos, P);
	//4: show a marker at this point

	//Visualizer::ShowMarker(P, flimColor::red);
	output = P;
	return errcode::success;
}




errcode FlimTerrain::FindNormalUnderPosition(const Vect& pos, Vect& output)
{
	//1: find cell
	int i = int(pos.Z() / cellDimension);
	int j = int(pos.X() / cellDimension);
	if (i >= imgHeight || j >= imgHeight || i + 1 >= imgHeight || j + 1 >= imgHeight)
	{
		return errcode::no_terrain;
		//return errcode::failure;
	}

	//2: determine which triangle in cell -- compare Vertex(i,j) - pos and Vertex(i+1, j+1) - pos
	Vect NW(pVerts[VertexIndex(i, j)].x, pVerts[VertexIndex(i, j)].y, pVerts[VertexIndex(i, j)].z);
	//Visualizer::ShowMarker(NW, flimColor::yellow);
	Vect SE(pVerts[VertexIndex(i + 1, j + 1)].x, pVerts[VertexIndex(i + 1, j + 1)].y, pVerts[VertexIndex(i + 1, j + 1)].z);
	//Visualizer::ShowMarker(SE, flimColor::yellow);

	//Visualizer::ShowLine(NW, pos);
	//Visualizer::ShowLine(SE, pos);

	//TriangleIndex triangle;

	Vect a, b, c;

	if ((NW - pos).magSqr() < (SE - pos).magSqr()) // use NW as 'a'
	{
		//triangle = tlist[TriIndex(i, j)]; // first triangle of pair

		a = NW;
		b = Vect(pVerts[VertexIndex(i, j + 1)].x, pVerts[VertexIndex(i, j + 1)].y, pVerts[VertexIndex(i, j + 1)].z);
		c = Vect(pVerts[VertexIndex(i + 1, j)].x, pVerts[VertexIndex(i + 1, j)].y, pVerts[VertexIndex(i + 1, j)].z);

	}
	else // use SE as 'a'
	{
		//triangle = tlist[TriIndex(i, j) + 1]; // second triangle of pair

		a = SE;
		b = Vect(pVerts[VertexIndex(i + 1, j)].x, pVerts[VertexIndex(i + 1, j)].y, pVerts[VertexIndex(i + 1, j)].z);
		c = Vect(pVerts[VertexIndex(i, j + 1)].x, pVerts[VertexIndex(i, j + 1)].y, pVerts[VertexIndex(i, j + 1)].z);

	}

	//3: make line plane intersection with three vertices that make up chosen triangle
	// -- define plane from three points
	//  a - b => AB, c - b => CB
	//  normal => AB.cross(CB)
	//  plane eqn is :     d = normalX*(a.x) + normalY*(a.y) + normalZ*(a.z)
	//  t = -(pos.dot(normal) + d) / (downVector.dot(normal)
	//  P = pos + t*(downVector)

	//Vect a(pVerts[triangle.v0].x, pVerts[triangle.v0].y, pVerts[triangle.v0].z);
	//Vect b(pVerts[triangle.v1].x, pVerts[triangle.v1].y, pVerts[triangle.v1].z);
	//Vect c(pVerts[triangle.v2].x, pVerts[triangle.v2].y, pVerts[triangle.v2].z);

	//Visualizer::ShowLine(a, b, flimColor::green);
	//Visualizer::ShowLine(c, b, flimColor::green);
	//Visualizer::ShowLine(c, a, flimColor::green);

	//Visualizer::ShowMarker(a, flimColor::green);
	//Visualizer::ShowMarker(b, flimColor::green);
	//Visualizer::ShowMarker(c, flimColor::green);

	Vect AB = b - a;
	Vect CB = c - a;
	Vect normal = AB.cross(CB).getNorm();

	Visualizer::ShowLine(normal, Vect(normal.X() + 10.0f, normal.Y() + 10.0f, normal.Z() + 10.0f));

	output = normal;
	return errcode::success;
}

errcode FlimTerrain::ShowNearestCells(const Collidable & coll)
{
	// 1: Generate 'AABB' from BSphere (just max/min vect)
	
	Vect maxBS = Vect(coll.getBSphere().getCenter().X() + coll.getBSphere().getRadius(), coll.getBSphere().getCenter().Y() + coll.getBSphere().getRadius(), coll.getBSphere().getCenter().Z() + coll.getBSphere().getRadius());
	Vect minBS = Vect(coll.getBSphere().getCenter().X() - coll.getBSphere().getRadius(), coll.getBSphere().getCenter().Y() - coll.getBSphere().getRadius(), coll.getBSphere().getCenter().Z() - coll.getBSphere().getRadius());
	
	Visualizer::ShowAABB(minBS, maxBS, flimColor::blue);
	Visualizer::ShowBSphere(coll.getBSphere(), flimColor::darkGray);
	Visualizer::ShowCollisionVolume(coll, flimColor::lightGray);

	// 2: Get iMax, jMax, iMin, jMin

	int iMax = static_cast<int>(abs(maxBS.Z() / cellDimension));
	int jMax = static_cast<int>(abs(maxBS.X() / cellDimension));
	int iMin = static_cast<int>(abs(minBS.Z() / cellDimension));
	int jMin = static_cast<int>(abs(minBS.X() / cellDimension));

	if (iMax >= imgHeight || jMax >= imgHeight)
	{
		return errcode::failure;
	}
	
	Vect min;
	Vect max;

	// 3: Nested-for loop to show group of cells underneath AABB
	for (int i = iMin; i < iMax; i++)
	{
		for (int j = jMin; j < jMax; j++)
		{
			if (FindMin(i, j, min) == errcode::success && FindMax(i, j, max) == errcode::success)
			{
				CollisionVolumeAABB aabb;
				aabb.SetMinMax(min, max);

				if (FlimMath::Intersect(coll.getBSphere(), aabb))
				{
					if (coll.GetCollisionVolume().Intersect(aabb))
					{
						Visualizer::ShowAABB(min, max, flimColor::red);
					}
					else
					{
						Visualizer::ShowAABB(min, max, flimColor::yellow);
					}
				}
				else
				{
					Visualizer::ShowAABB(min, max, flimColor::green);
				}
			}
			else
			{
				return errcode::failure;
			}
		}
	}

	return errcode::success;

}


