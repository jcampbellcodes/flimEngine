#pragma once
#ifndef ImageManager_H
#define ImageManager_H

#include "AzulCore.h"
#include <map>
#include "err.h"

class ImageManager
{
private:

	//big four
	ImageManager();
	ImageManager(const ImageManager&) = default;
	const ImageManager& operator= (const ImageManager&) = delete;
	~ImageManager();

	// singleton pointer + accessor
	static ImageManager* instance;

	static ImageManager& Instance()
	{
		if (instance == nullptr)
		{
			instance = new ImageManager();
		}
		return *instance;
	}

	// needs an intenal hashmap
	std::map<std::string, Image*> ImagePool;

	//default path
	const std::string defaultPath = "Images/";


	errcode privLoadImage(Image*& output, std::string key, std::string path);

	errcode privLoadImage(Image*& output, std::string key, std::string path, Rect* area);

	errcode privGetImage(Image*& output, std::string key);

	const Image& privGetImage(std::string key);

	errcode privUnloadImages();

	friend class FlimSprite;
	Model* spriteModel;
	static Model* getSpriteModel();

	ShaderObject* spriteShader;
	static ShaderObject* getSpriteShader();


public:



	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Image& ImageManager::LoadImage(std::string key, std::string path)
	///
	/// \brief	Loads a Image.
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param	key 	The key.
	/// \param	path	Full pathname of the file.
	/// 				
	///
	/// \return	The Image.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Image& Load(std::string key, std::string path) // assumes we are loading the entire texture
	{

		Image* image = nullptr;
		assert((Instance().privLoadImage(image, key, path) == errcode::success) && "Image key not unique -- choose another");
		Instance().privLoadImage(image, key, path);
		return *image;
	};

	static Image& Load(std::string key, std::string path, Rect* area) // assumes we are loading the entire texture
	{

		Image* image = nullptr;
		assert((Instance().privLoadImage(image, key, path, area) == errcode::success) && "Image key not unique -- choose another");
		Instance().privLoadImage(image, key, path);
		return *image;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Image& ImageManager::GetImage(std::string key)
	///
	/// \brief	Gets a Image.
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param	String ID of Image
	///
	/// \return	The Image.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Image& Get(std::string key)
	{
		Image* image = nullptr;
		assert((Instance().privGetImage(image, key) == errcode::success) && "Image not found with the key you provided");
		return *image;
	};


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode ImageManager::UnloadImages()
	///
	/// \brief	Unload all Images -- to be used in a destructor
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode UnloadImages() { return Instance().privUnloadImages(); };

};

#endif ImageManager_H
