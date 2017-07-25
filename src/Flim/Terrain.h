#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "AzulCore.h"
#include "GameObject.h"
#include "CollisionVolumeBSphere.h"
class Texture;
class Model;
struct VertexStride_VUN;
struct TriangleIndex;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	FlimTerrain
///
/// \brief	A flim terrain.
/// \ingroup TERRAIN
/// \author	Jack Campbell
/// \date	6/1/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class FlimTerrain : public GameObject
{
public:
	// big four
	FlimTerrain() = delete;

	// takes in heightmap, gets array of pixel values stored bottom left to upper right of TGA heightmap
	FlimTerrain(const char*, float sideLength, float _maxHeight, float _zeroAltitude);

	FlimTerrain(const FlimTerrain&) = default;
	FlimTerrain& operator=(const FlimTerrain&) = default;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	FlimTerrain::FlimTerrain(const char * heightmapFile, const char * texturePath, float _sideLength, float _maxHeight, float _zeroAltitude, float U, float V);
	///
	/// \brief	Constructor.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param	heightmapFile	The heightmap file.
	/// \param	texturePath  	Full pathname of the texture file.
	/// \param	_sideLength  	Length of the side.
	/// \param	_maxHeight   	The maximum height.
	/// \param	_zeroAltitude	The zero altitude.
	/// \param	U			 	The float to process.
	/// \param	V			 	The float to process.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	FlimTerrain(const char * heightmapFile, const char * texturePath, float _sideLength, float _maxHeight, float _zeroAltitude, float U, float V);
	errcode ActivateTerrain();
	errcode DeactivateTerrain();
	~FlimTerrain();

	// acccesors
	int VertexIndex(int i, int j);
	int PixelIndex(int i, int j);
	float PixelToFloat(unsigned char hval);
	int TriIndex(int i, int j);

	void ShowCells();

	// cells
	errcode FindMax(int i, int j, Vect& out);
	errcode FindMin(int i, int j, Vect& out);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode FlimTerrain::ShowNearestCell(const Vect& pos);
	///
	/// \brief	Shows the nearest cell.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param	pos	The position.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode ShowNearestCell(const Vect& pos);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	CollisionVolumeAABB FlimTerrain::FindNearestCell(const Vect & pos);
	///
	/// \brief	Searches for the nearest cell.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param	pos	The position.
	///
	/// \return	The found cell.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CollisionVolumeAABB FindNearestCell(const Vect & pos);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode FlimTerrain::ShowExactPosition(const Vect & pos);
	///
	/// \brief	Shows the exact position.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param	pos	The position.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode ShowExactPosition(const Vect & pos);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	Vect FlimTerrain::GetNormalizedPosition(const Vect & pos);
	///
	/// \brief	Gets normalized position.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param	pos	The position.
	///
	/// \return	The normalized position.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Vect GetNormalizedPosition(const Vect & pos);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode FlimTerrain::GetExactPosition(const Vect & pos, Vect & output);
	///
	/// \brief	Gets exact position.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param 		   	pos   	The position.
	/// \param [in,out]	output	The output.
	///
	/// \return	The exact position.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode GetExactPosition(const Vect & pos, Vect & output);
	//Vect GetExactPosition(const Vect & pos);
	//Vect FindNormalUnderPosition(const Vect & pos);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode FlimTerrain::FindNormalUnderPosition(const Vect & pos, Vect & output);
	///
	/// \brief	Searches for the first normal under position.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param 		   	pos   	The position.
	/// \param [in,out]	output	The output.
	///
	/// \return	The found normal under position.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode FindNormalUnderPosition(const Vect & pos, Vect & output);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	errcode FlimTerrain::ShowNearestCells(const Collidable & coll);
	///
	/// \brief	Shows the nearest cells.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param	coll	The collection.
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	errcode ShowNearestCells(const Collidable & coll);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	float FlimTerrain::getCellDimension() const
	///
	/// \brief	Gets cell dimension.
	/// \ingroup TERRAIN
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	The cell dimension.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	float getCellDimension() const { return cellDimension; };

	errcode Draw();



private:
	// terrain model
	Model* terrainModel;
	// terrain user data
	float terrainSideLength;
	float maxHeight;
	float zeroAltitutde;

	int pixel_width;

	GraphicsObject_TextureLight* terrainGO;
	//GraphicsObject_TextureFlat* terrainGO;
	GraphicsObject_WireframeConstantColor* terrainGOWire;

	float cellDimension;
	int NUM_VERTS;
	int NUM_TRIS;
	int imgWidth;
	int imgHeight;


	// support methods
	

	// terrain graphics data
	VertexStride_VUN* pVerts;
	TriangleIndex* tlist;
	GLbyte* imgData;


	Texture* terrainTexture;

};

#endif