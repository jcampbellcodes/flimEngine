#pragma once
#ifndef TerrainMANAGER_H
#define TerrainMANAGER_H
#include <map>
#include "AzulCore.h"
#include "err.h"
#include "Terrain.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	TerrainManager
///
/// \ingroup TERRAIN
/// \brief	Manager for terrains.
///
/// \author	Jack Campbell
/// \date	6/1/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class TerrainManager
{
private:

	//big four
	TerrainManager() = default;
	TerrainManager(const TerrainManager&) = default;
	const TerrainManager& operator= (const TerrainManager&) = delete;
	~TerrainManager();

	// singleton pointer + accessor
	static TerrainManager* instance;

	static TerrainManager& Instance()
	{
		if (instance == nullptr)
		{
			instance = new TerrainManager();
		}
		return *instance;
	}

	// needs an intenal hashmap
	std::map<std::string, FlimTerrain*> TerrainPool;

	//default path
	const std::string defaultPath = "Terrains/";


	errcode privLoadTerrain(std::string key, const char* heightMapPath, const char* texturePath = "grid", float _sideLength = 100.0f, float _maxHeight = 10.0f, float _zeroAltitude = 0.0f, float U = 30.0f, float V = 30.0f);

	errcode privGetTerrain(FlimTerrain *& output, std::string key);

	errcode privUnloadTerrains();

public:

	// load or add a Terrain
	// takes a pointer reference pOut, a string ID to access, path relative to Assets folder

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Terrain& TerrainManager::LoadTerrain(std::string key, std::string path)
	///
	/// \brief	Loads a Terrain.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \ingroup RESOURCEMANAGERS
	/// \ingroup TERRAIN
	/// \param	key 	The key.
	/// \param	path	Full pathname of the file.
	///
	/// \return	The Terrain.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode LoadTerrain(std::string key, const char* heightMapPath, const char* texturePath = "grid", float _sideLength = 100.0f, float _maxHeight = 10.0f, float _zeroAltitude = 0.0f, float U = 30.0f, float V = 30.0f)
	{
		return Instance().privLoadTerrain(key, heightMapPath, texturePath, _sideLength, _maxHeight, _zeroAltitude, U, V);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode TerrainManager::GetTerrain(FlimTerrain *& output, std::string key)
	///
	/// \brief	Gets a terrain.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	/// \ingroup TERRAIN
	/// \param [in,out]	output	[in,out] If non-null, the output.
	/// \param 		   	key   	The key.
	///
	/// \return	The terrain.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode GetTerrain(FlimTerrain *& output, std::string key)
	{
		return Instance().privGetTerrain(output, key);
	}

	// unload all Terrains -- to be used in a destructor

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode TerrainManager::UnloadTerrains()
	///
	/// \brief	Unload Terrains.
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \ingroup TERRAIN
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode UnloadTerrains() { return Instance().privUnloadTerrains(); };

};

#endif TerrainMANAGER_H
