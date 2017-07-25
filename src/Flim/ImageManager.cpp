#include "ImageManager.h"
#include "TextureManager.h"
#include "err.h" 
#include "ShaderManager.h"

ImageManager* ImageManager::instance = nullptr;

ImageManager::~ImageManager()
{
	//DebugMsg::out("ImageManager cleaned\n");

}

ImageManager::ImageManager()
{
	this->spriteModel = new Model(Model::PreMadedeModels::UnitSquareXY); 
	this->spriteShader = &ShaderManager::GetShader("__FLIM__spriteRender");
}

errcode ImageManager::privLoadImage(Image *& output, std::string key, std::string path)
{
	//check for duplicate
	std::map<std::string, Image*>::iterator iter = this->ImagePool.find(key);

	// means it isn't found
	if (iter == this->ImagePool.end())
	{
		std::string catPath = this->defaultPath + path;

		// load texture, get its dimensions since we want the whole thing
		Texture& texture = TextureManager::LoadTexture(key, path);

		// make a new Image at the path
		Image *newImage = nullptr;

		newImage = new Image(&texture, new Rect(0.0f, 0.0f, (float)texture.getWidth(), (float)texture.getHeight()));
		if (!newImage)
		{
			return errcode::failure;
		}

		// add its pointer to the map and assign to the key
		this->ImagePool.insert(std::pair<std::string, Image*>(key, newImage));

		// set output to the loaded Image pointer
		output = newImage;

		return errcode::success;
	}
	else
	{
		//duplicate
		return errcode::failure;
	}
}

errcode ImageManager::privLoadImage(Image *& output, std::string key, std::string path, Rect* area)
{
	//check for duplicate
	std::map<std::string, Image*>::iterator iter = this->ImagePool.find(key);

	if (!area)
	{
		return errcode::failure;
	}

	// means it isn't found
	if (iter == this->ImagePool.end())
	{
		std::string catPath = this->defaultPath + path;

		// load texture, get its dimensions since we want the whole thing
		Texture& texture = TextureManager::LoadTexture(key, path);

		// make a new Image at the path
		Image *newImage = nullptr;
		
		newImage = new Image(&texture, area);
		if (!newImage)
		{
			return errcode::failure;
		}

		// add its pointer to the map and assign to the key
		this->ImagePool.insert(std::pair<std::string, Image*>(key, newImage));

		// set output to the loaded Image pointer
		output = newImage;

		return errcode::success;
	}
	else
	{
		//duplicate
		return errcode::failure;
	}
}

errcode ImageManager::privGetImage(Image *& output, std::string key)
{
	//check for duplicate
	std::map<std::string, Image*>::iterator iter = this->ImagePool.find(key);

	if (iter != this->ImagePool.end())
	{
		// get a pointer to the Image by giving the key to the map
		output = this->ImagePool.at(key);
	}
	else
	{
		//not found
		return errcode::failure;
	}

	return errcode::success;
}

const Image& ImageManager::privGetImage(std::string key)
{
	return *this->ImagePool.at(key);
}

errcode ImageManager::privUnloadImages()
{
	// clean up the map
	std::map<std::string, Image*>::iterator iter = this->ImagePool.begin();

	while (iter != this->ImagePool.end())
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
	this->ImagePool.clear();


	if (instance)
	{
		delete instance;
		instance = nullptr;
	}

	return errcode::success;
}

Model * ImageManager::getSpriteModel()
{
	return Instance().spriteModel;
}

ShaderObject * ImageManager::getSpriteShader()
{
	return Instance().spriteShader;
}
