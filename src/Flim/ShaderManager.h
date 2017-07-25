#pragma once
#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include "AzulCore.h"
#include <map>
#include "err.h"

class ShaderManager
{
private:

	//big four
	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = default;
	const ShaderManager& operator= (const ShaderManager&) = delete;
	~ShaderManager();

	// singleton pointer + accessor
	static ShaderManager* instance;

	static ShaderManager& Instance()
	{
		if (instance == nullptr)
		{
			instance = new ShaderManager();
		}
		return *instance;
	}

	// needs an intenal hashmap
	std::map<std::string, ShaderObject*> ShaderPool;

	//default path
	const std::string defaultPath = "Shaders/";

	errcode privLoadShader(ShaderObject*& output, std::string key, std::string path);

	errcode privGetShader(ShaderObject*& output, std::string key);

	errcode privUnloadShaders();
	errcode privLoadDefaultShaders();

	const ShaderObject& privGetShader(std::string key);

public:

	// load or add a Shader
	// takes a pointer reference pOut, a string ID to access, path relative to Assets folder

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static ShaderObject& ShaderManager::LoadShader(std::string key, std::string path)
	///
	/// \brief	Loads a shader.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup RESOURCEMANAGERS
	/// \param	key 	The key.
	/// \param	path	Full pathname of the file.
	///
	/// \return	The shader.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static ShaderObject& LoadShader(std::string key, std::string path)
	{
		ShaderObject* Shader = nullptr;
		assert((Instance().privLoadShader(Shader, key, path) == errcode::success) && "Shader key not unique -- choose another");
		Instance().privLoadShader(Shader, key, path);
		return *Shader;
	};

	// get a Shader
	// returns error code -- takes in string ID of Shader and object for output

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static ShaderObject& ShaderManager::GetShader(std::string key)
	///
	/// \brief	Gets a shader.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///\ingroup RESOURCEMANAGERS
	/// \param	key	The key.
	/// 			
	/// \par These keys can be used to load default shaders.
	/// 	 
	/// 	  \code
	/// 	__FLIM__spriteRender
	/// \endcode
	/// \code
	/// 	__FLIM__spriteLineRender
	/// \endcode
	/// \code
	/// 	__FLIM__textureFlatRender
	/// 	 \endcode
	/// \code
	/// 	__FLIM__textureLightRender
	/// 	 \endcode
	/// \code
	/// 	__FLIM__colorNoTextureRender
	/// 	 \endcode
	/// \code
	/// 	__FLIM__colorConstantRender
	/// 	 \endcode
	///
	///
	///
	///
	/// \return	The shader.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static ShaderObject& GetShader(std::string key)
	{
		ShaderObject* Shader = nullptr;
		assert((Instance().privGetShader(Shader, key) == errcode::success) && "Shader not found with the key you provided");
		return *Shader;
	};

	// unload all Shaders -- to be used in a destructor

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode ShaderManager::UnloadShaders()
	///
	/// \brief	Unload shaders.
	///\ingroup RESOURCEMANAGERS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode UnloadShaders() { return Instance().privUnloadShaders(); };

	static errcode LoadDefaultShaders()
	{
		return Instance().privLoadDefaultShaders();
	}

};

#endif SHADERMANAGER_H
