#pragma once
#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "AzulCore.h"
#include <map>
#include "err.h"

class ModelManager
{
private:

	//big four
	ModelManager() = default;
	ModelManager(const ModelManager&) = default;
	const ModelManager& operator= (const ModelManager&) = delete;
	~ModelManager();

	// singleton pointer + accessor
	static ModelManager* instance;

	static ModelManager& Instance()
	{
		if (instance == nullptr)
		{
			instance = new ModelManager();
		}
		return *instance;
	}

	// needs an intenal hashmap
	std::map<std::string, Model*> ModelPool;

	//default path
	const std::string defaultPath = "Models/";


	errcode privLoadModel(Model*& output, std::string key, std::string path);

	errcode privGetModel(Model*& output, std::string key);

	const Model& privGetModel(std::string key);

	errcode privUnloadModels();
	errcode privLoadDefaultModels();
	GraphicsObject_TextureLight* privGenerateGraphicsObject(std::string key);

public:



	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Model& ModelManager::LoadModel(std::string key, std::string path)
	///
	/// \brief	Loads a model.
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param	key 	The key.
	/// \param	path	Full pathname of the file.
	/// 				
	///
	/// \return	The model.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Model& LoadModel(std::string key, std::string path)
	{
		Model* Model = nullptr;
		assert((Instance().privLoadModel(Model, key, path) == errcode::success) && "Model key not unique -- choose another");
		Instance().privLoadModel(Model, key, path);
		return *Model;
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Model& ModelManager::GetModel(std::string key)
	///
	/// \brief	Gets a model.
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param	String ID of Model
	///
	/// \return	The model.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Model& GetModel(std::string key)
	{
		Model* Model = nullptr;
		assert((Instance().privGetModel(Model, key) == errcode::success) && "Model not found with the key you provided");
		return *Model;
	};


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode ModelManager::UnloadModels()
	///
	/// \brief	Unload all Models -- to be used in a destructor
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode UnloadModels() { return Instance().privUnloadModels(); };

	static GraphicsObject_TextureLight* GenerateGraphicsObject(std::string key) { return Instance().privGenerateGraphicsObject(key); };

	static errcode LoadDefaultModels() { return Instance().privLoadDefaultModels(); };

};

#endif MODELMANAGER_H
