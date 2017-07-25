
#include "ShaderManager.h"
#include "err.h"

ShaderManager* ShaderManager::instance = nullptr;

ShaderManager::~ShaderManager()
{
	//DebugMsg::out("ShaderManager cleaned\n");

}

errcode ShaderManager::privLoadShader(ShaderObject *& output, std::string key, std::string path)
{
	//check for duplicate
	std::map<std::string, ShaderObject*>::iterator iter = this->ShaderPool.find(key);

	// means it isn't found
	if (iter == this->ShaderPool.end())
	{
		std::string catPath = this->defaultPath + path;
		// make a new Shader at the path
		ShaderObject *newShader = nullptr;
		newShader = new ShaderObject(catPath.c_str());
		if (!newShader)
		{
			return errcode::failure;
		}

		// add its pointer to the map and assign to the key
		this->ShaderPool.insert(std::pair<std::string, ShaderObject*>(key, newShader));

		// set output to the loaded Shader pointer
		output = newShader;

		return errcode::success;
	}
	else
	{
		//duplicate
		return errcode::failure;
	}
}

errcode ShaderManager::privGetShader(ShaderObject *& output, std::string key)
{
	//check for duplicate
	std::map<std::string, ShaderObject*>::iterator iter = this->ShaderPool.find(key);

	if (iter != this->ShaderPool.end())
	{
		// get a pointer to the Shader by giving the key to the map
		output = this->ShaderPool.at(key);
	}
	else
	{
		//not found
		return errcode::failure;
	}

	return errcode::success;
}

const ShaderObject& ShaderManager::privGetShader(std::string key)
{
	return *this->ShaderPool.at(key);
}

errcode ShaderManager::privUnloadShaders()
{
	// clean up the map
	std::map<std::string, ShaderObject*>::iterator iter = this->ShaderPool.begin();

	while (iter != this->ShaderPool.end())
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
	this->ShaderPool.clear();

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}

	return errcode::success;
}

errcode ShaderManager::privLoadDefaultShaders()
{
	errcode err = errcode::success;
	ShaderObject* sh = nullptr;
	err = privLoadShader(sh, "__FLIM__spriteRender", "spriteRender");
	err = privLoadShader(sh, "__FLIM__spriteLineRender", "spriteLineRender");
	err = privLoadShader(sh, "__FLIM__textureFlatRender", "textureFlatRender");
	err = privLoadShader(sh, "__FLIM__textureLightRender", "textureLightRender");
	err = privLoadShader(sh, "__FLIM__colorNoTextureRender", "colorNoTextureRender");
	err = privLoadShader(sh, "__FLIM__colorConstantRender", "colorConstantRender");

	return err;
}
