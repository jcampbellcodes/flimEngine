#include "TextureManager.h"
#include "err.h"

TextureManager* TextureManager::instance = nullptr;

TextureManager::~TextureManager()
{
	//DebugMsg::out("Texure manager cleaned\n");

}

errcode TextureManager::privLoadTexture(Texture *& output, std::string key, std::string path)
{
	//check for duplicate
	std::map<std::string, Texture*>::iterator iter = this->TexturePool.find(key);

	// means it isn't found
	if (iter == this->TexturePool.end())
	{
		std::string catPath = this->defaultPath + path;
		// make a new Texture at the path
		Texture *newTexture = nullptr;
		newTexture = new Texture(catPath.c_str());
		if (!newTexture)
		{
			return errcode::failure;
		}

		// add its pointer to the map and assign to the key
		this->TexturePool.insert(std::pair<std::string, Texture*>(key, newTexture));

		// set output to the loaded Texture pointer
		output = newTexture;

		return errcode::success;
	}
	else
	{
		//duplicate
		return errcode::failure;
	}
}

errcode TextureManager::privGetTexture(Texture *& output, std::string key)
{
	//check for duplicate
	std::map<std::string, Texture*>::iterator iter = this->TexturePool.find(key);

	if (iter != this->TexturePool.end())
	{
		// get a pointer to the Texture by giving the key to the map
		output = this->TexturePool.at(key);
	}
	else
	{
		//not found
		return errcode::failure;
	}

	return errcode::success;
}



errcode TextureManager::privUnloadTextures()
{
	// clean up the map
	std::map<std::string, Texture*>::iterator iter = this->TexturePool.begin();

	while (iter != this->TexturePool.end())
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
	this->TexturePool.clear();


	if (instance)
	{
		delete instance;
		instance = nullptr;
	}

	return errcode::success;
}
