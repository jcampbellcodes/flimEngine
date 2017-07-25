#ifndef Flim_H
#define Flim_H

#include "AzulCore.h"
#include <string>

class Flim: public Engine
{
private:
	// constructor
	Flim()
	{};
    
	Flim(const Flim&) = delete;
	Flim& operator=(const Flim&) = delete;

	~Flim();

	static Flim* instance;
	static Flim& Instance()
	{
		if (!instance)
		{
			instance = new Flim();
		}
		return *instance;
	}


	// Methods Users need to overloade in their Flim
    virtual void Initialize();
    virtual void LoadContent();
	virtual void Update();
    virtual void Draw();
    virtual void UnLoadContent();

	std::string name;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void Flim::GameTerminate();
	///
	/// \brief	Game terminate.
	/// \ingroup ENGINECALLBACKS
	/// 		 
	/// \par A callback hook for when the game is just about to unload all content.
	///
	/// \author	Jack Campbell
	/// \date	3/12/2017
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameTerminate();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void Flim::LoadResources();
	///
	/// \brief	User area to load resources.
	/// 		
	/// \ingroup ENGINECALLBACKS
	/// 		 
	/// \par Load resources here. These keys can be used for default shaders:
	/// 	 
	/// \code
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
	/// 		 
	/// \code
	/// 	
	/// void Flim::LoadResources()
	/// {
	///	//---------------------------------------------------------------------------------------------------------
	///	// Load the Models
	///	//---------------------------------------------------------------------------------------------------------
	///
	///	ModelManager::LoadModel("space_frigate", "space_frigate.azul");
	///	ModelManager::LoadModel("Axis", "Axis.azul");
	///	ModelManager::LoadModel("Plane", "Plane.azul");
	///	ModelManager::LoadModel("Cottage", "Cottage.azul");
	///	ModelManager::LoadModel("Sphere", "sphere.azul");
	///
	///	//---------------------------------------------------------------------------------------------------------
	///	// Load the Textures
	///	//---------------------------------------------------------------------------------------------------------
	///
	///	TextureManager::LoadTexture("space_frigate", "space_frigate.tga");
	///	TextureManager::LoadTexture("Cottage", "stitch.tga");
	///	TextureManager::LoadTexture("grid", "grid.tga");
	///	TextureManager::LoadTexture("Sphere", "sphere.tga");
	///
	///	//---------------------------------------------------------------------------------------------------------
	///	// Load the Shaders
	///	//---------------------------------------------------------------------------------------------------------
	///
	///	ShaderManager::LoadShader("__FLIM__textureFlatRender", "textureFlatRender");
	///	ShaderManager::LoadShader("__FLIM__textureLightRender", "textureLightRender");
	///	ShaderManager::LoadShader("__FLIM__colorNoTextureRender", "colorNoTextureRender");
	///	ShaderManager::LoadShader("__FLIM__colorConstantRender", "colorConstantRender");
	///
	///
	///	SceneManager::SetStartScene(new FirstScene);
	/// }
	///
	/// \endcode
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void LoadResources();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	void Flim::GameInitialize();
	///
	/// \brief	Callback to offer access to game initialization.
	/// \ingroup ENGINECALLBACKS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameInitialize();

	friend class FlimTime; // offers time this data
	static float GetTime()
	{
		return Instance().GetTimeInSeconds();
	}

	Vect privGetColor();

	std::string privGetWindowName();


public:	

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static void Flim::Run()
	///
	/// \brief	Runs the game.
	///
	/// \author	Jack Campbell
	/// \date	3/5/2017
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void Run()
	{
		Instance().run();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static int Flim::GetHeight()
	///
	/// \brief	Gets the height of the window.
	/// \ingroup ENGINE
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \return	The height.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static int GetHeight()
	{
		return Instance().getHeight();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static int Flim::GetWidth()
	///
	/// \brief	Gets the width of the window.
	///\ingroup ENGINE
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par Get the integer width of the window.
	/// \code
	/// 	 
	/// 	 int windowWidth = Flim::GetWidth();
	/// 	 
	/// \endcode
	///
	/// \return	The width.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static int GetWidth()
	{
		return Instance().getWidth();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static void Flim::SetColor(float r, float g, float b, float a)
	///
	/// \brief	Sets an RGBA color for the background.
	///\ingroup ENGINE
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par Sets the color that appears behind all other rendered graphics objects, takes NORMALIZED RGBA values.
	/// 	 Red, green, yellow, alpha (transparency). Google "normalized RGBA color picker" to visualize a color before you use it.
	/// 	 
	/// \code
	/// 	 
	/// 	 // black
	/// 	 Flim::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	/// 	 
	/// \endcode
	///
	/// \param	r	R component of color.
	/// \param	g	G component of color.
	/// \param	b	B component of color.
	/// \param	a	A component of color.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void SetColor(float r, float g, float b, float a)
	{
		Instance().SetClearColor(r, g, b, a);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static void Flim::SetWidthHeight(int x, int y)
	///
	/// \brief	Sets width and height of window.
	///\ingroup ENGINE
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// 
	/// \par Get the integer height of the window.
	/// \code
	///
	/// 	 int windowHeight = Flim::GetHeight();
	///
	/// \endcode
	/// 
	/// 
	/// \param	x	The x coordinate.
	/// \param	y	The y coordinate.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void SetWidthHeight(int x, int y)
	{
		Instance().SetWidthHeight(x, y);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static void Flim::SetWindowName(char* in)
	///
	/// \brief	Sets window name.
	///\ingroup ENGINE
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \par Sets the text that appears at the top of the game window.
	///
	/// \param [in,out]	in	If non-null, the in.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static void SetWindowName(char* in)
	{
		Instance().name = std::string(in);
		Instance().setWindowName(in);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static std::string Flim::GetWindowName()
	///
	/// \brief	Gets window name.
	/// \ingroup ENGINE
	/// \author	Jack Campbell
	/// \date	3/12/2017
	///
	/// \par Returns the name of the Window.
	/// 
	/// \return	The window name.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static std::string GetWindowName()
	{
		return Instance().privGetWindowName();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static Vect& Flim::GetColor()
	///
	/// \brief	Gets the color.
	/// \ingroup ENGINE
	///
	/// \author	Jack Campbell
	/// \date	3/12/2017
	///
	/// \return	The color.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static Vect GetColor()
	{
		return Instance().privGetColor();
	}

	// legacy
	//Flim( const char* windowName, const int Width,const int Height);



};

#endif