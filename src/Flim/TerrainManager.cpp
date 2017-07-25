#include "TerrainManager.h"
#include "err.h"

TerrainManager* TerrainManager::instance = nullptr;

TerrainManager::~TerrainManager()
{
	//DebugMsg::out("Texure manager cleaned\n");

}



errcode TerrainManager::privLoadTerrain(std::string key, const char* heightMapPath, const char* texturePath, float _sideLength, float _maxHeight, float _zeroAltitude, float U, float V)
{
	//check for duplicate
	std::map<std::string, FlimTerrain*>::iterator iter = this->TerrainPool.find(key);

	// means it isn't found
	if (iter == this->TerrainPool.end())
	{
		std::string catPath = this->defaultPath + texturePath;
		// make a new Terrain at the path
		FlimTerrain *newTerrain = nullptr;

		newTerrain = new FlimTerrain(heightMapPath, texturePath, _sideLength, _maxHeight, _zeroAltitude, U, V);
		if (!newTerrain)
		{
			return errcode::failure;
		}

		// add its pointer to the map and assign to the key
		this->TerrainPool.insert(std::pair<std::string, FlimTerrain*>(key, newTerrain));

		return errcode::success;
	}
	else
	{
		//duplicate
		return errcode::failure;
	}
}


errcode TerrainManager::privGetTerrain(FlimTerrain *& output, std::string key)
{
	//check for duplicate
	std::map<std::string, FlimTerrain*>::iterator iter = this->TerrainPool.find(key);

	if (iter != this->TerrainPool.end())
	{
		// get a pointer to the FlimTerrain by giving the key to the map
		output = this->TerrainPool.at(key);
	}
	else
	{
		//not found
		return errcode::failure;
	}

	return errcode::success;
}

errcode TerrainManager::privUnloadTerrains()
{
	// clean up the map
	std::map<std::string, FlimTerrain*>::iterator iter = this->TerrainPool.begin();

	while (iter != this->TerrainPool.end())
	{
		if (iter->second)
		{
			delete iter->second;
		}
		else
		{
			return errcode::failure;
		}
		iter++;
	}
	this->TerrainPool.clear();


	if (instance)
	{
		delete instance;
		instance = nullptr;
	}

	return errcode::success;
}
