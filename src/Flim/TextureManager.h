#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <map>
#include "AzulCore.h"
#include "err.h"

class TextureManager
{
private:

	//big four
	TextureManager() = default;
	TextureManager(const TextureManager&) = default;
	const TextureManager& operator= (const TextureManager&) = delete;
	~TextureManager();

	// singleton pointer + accessor
	static TextureManager* instance;

	static TextureManager& Instance()
	{
		if (instance == nullptr)
		{
			instance = new TextureManager();
		}
		return *instance;
	}

	// needs an intenal hashmap
	std::map<std::string, Texture*> TexturePool;

	//default path
	const std::string defaultPath = "Textures/";


	errcode privLoadTexture(Texture*& output, std::string key, std::string path);
	
	errcode privGetTexture(Texture*& output, std::string key);
	
	const Texture& privGetTexture(std::string key);
	
	errcode privUnloadTextures();

public:

	// load or add a texture
	// takes a pointer reference pOut, a string ID to access, path relative to Assets folder

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Texture& TextureManager::LoadTexture(std::string key, std::string path)
	///
	/// \brief	Loads a texture.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// \ingroup RESOURCEMANAGERS
	/// \param	key 	The key.
	/// \param	path	Full pathname of the file.
	///
	/// \return	The texture.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Texture& LoadTexture(std::string key, std::string path) 
	{ 
		Texture* texture = nullptr;
		assert((Instance().privLoadTexture(texture, key, path) == errcode::success) && "Texture key not unique -- choose another");
		Instance().privLoadTexture(texture, key, path);
		return *texture;
	};

	// get a texture
	// returns error code -- takes in string ID of texture and object for output

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Texture& TextureManager::GetTexture(std::string key)
	///
	/// \brief	Gets a texture.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup RESOURCEMANAGERS
	/// \param	key	The key.
	///
	/// \return	The texture.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Texture& GetTexture(std::string key) 
	{
		Texture* texture = nullptr;
		assert((Instance().privGetTexture(texture, key) == errcode::success) && "Texture not found with the key you provided");
		return *texture;
	};

	// unload all textures -- to be used in a destructor

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode TextureManager::UnloadTextures()
	///
	/// \brief	Unload textures.
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode UnloadTextures() { return Instance().privUnloadTextures(); };

};

#endif TEXTUREMANAGER_H
