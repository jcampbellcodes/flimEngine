#include "ModelManager.h"
#include "err.h" 
#include "TextureManager.h"
#include <vector>
#include "Texture.h"
#include "ShaderManager.h"
ModelManager* ModelManager::instance = nullptr;

ModelManager::~ModelManager()
{
	//DebugMsg::out("ModelManager cleaned\n");

}

errcode ModelManager::privLoadModel(Model *& output, std::string key, std::string path)
{
	//check for duplicate
	std::map<std::string, Model*>::iterator iter = this->ModelPool.find(key);

	// means it isn't found
	if (iter == this->ModelPool.end())
	{
		std::string catPath = this->defaultPath + path;
		// make a new Model at the path
		Model *newModel = nullptr;
		newModel = new Model(catPath.c_str());
		int i = 0;
		while (i < newModel->getTextureNum())
		{
			char* modelTextureName = newModel->getTextureName(i);
			TextureManager::LoadTexture(std::string("__FLIM_DEFAULT" + std::string(modelTextureName)), std::string(std::string(modelTextureName)));
			i++;
		}

		if (!newModel)
		{
			return errcode::failure;
		}

		// add its pointer to the map and assign to the key
		this->ModelPool.insert(std::pair<std::string, Model*>(key, newModel));

		// set output to the loaded Model pointer
		output = newModel;

		return errcode::success;
	}
	else
	{
		//duplicate
		return errcode::failure;
	}
}

errcode ModelManager::privGetModel(Model *& output, std::string key)
{
	//check for duplicate
	std::map<std::string, Model*>::iterator iter = this->ModelPool.find(key);

	if (iter != this->ModelPool.end())
	{
		// get a pointer to the Model by giving the key to the map
		output = this->ModelPool.at(key);
	}
	else
	{
		//not found
		return errcode::failure;
	}

	return errcode::success;
}

const Model& ModelManager::privGetModel(std::string key)
{
	return *this->ModelPool.at(key);
}

errcode ModelManager::privUnloadModels()
{
	// clean up the map
	std::map<std::string, Model*>::iterator iter = this->ModelPool.begin();

	while (iter != this->ModelPool.end())
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
	this->ModelPool.clear();


	if (instance)
	{
		delete instance;
		instance = nullptr;
	}

	return errcode::success;
}

errcode ModelManager::privLoadDefaultModels()
{
	Model* mod = nullptr;
	return privLoadModel(mod, "FLIMSPRITEMODEL", "SpriteModel.azul");
}

GraphicsObject_TextureLight * ModelManager::privGenerateGraphicsObject(std::string key)
{
	GraphicsObject_TextureLight* go = nullptr;
	Model* model = &ModelManager::GetModel(key);
	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	std::vector<Texture*> textures;

	int i = 0;
	while (i < model->getTextureNum())
	{
		char* modelTextureName = model->getTextureName(i);
		
		textures.push_back(&TextureManager::GetTexture(std::string("__FLIM_DEFAULT" + std::string(modelTextureName))));
		i++;
	}

	// how can i......... not do this.......
	switch (model->getTextureNum())
	{
		case 1:
		{
			go = new GraphicsObject_TextureLight(model, &ShaderManager::GetShader("__FLIM__textureLightRender"), textures.at(0), LightColor, LightPos);
			break;
		}
		case 2:
		{
			go = new GraphicsObject_TextureLight(model, &ShaderManager::GetShader("__FLIM__textureLightRender"), textures.at(0), textures.at(1), LightColor, LightPos);
			break;
		}
		case 3:
		{
			go = new GraphicsObject_TextureLight(model, &ShaderManager::GetShader("__FLIM__textureLightRender"), textures.at(0), textures.at(1), textures.at(2), LightColor, LightPos);
			break;
		}
		case 4:
		{
			go = new GraphicsObject_TextureLight(model, &ShaderManager::GetShader("__FLIM__textureLightRender"), textures.at(0), textures.at(1), textures.at(2), textures.at(3), LightColor, LightPos);
			break;
		}
		default:
		{
			go = new GraphicsObject_TextureLight(model, &ShaderManager::GetShader("__FLIM__textureLightRender"), &TextureManager::GetTexture("default"), LightColor, LightPos);
			break;
		}
	}

	return go;
}
