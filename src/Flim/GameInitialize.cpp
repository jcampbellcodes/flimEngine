#include "Flim.h"

#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"

#include <time.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	void Flim::GameInitialize()
///
/// \brief	Game initialize.
///
/// \author	Jack Campbell
/// \date	3/6/2017
/// 	
/// 
/// 			
/// 			
/// 					
/// \code
/// 	 
/// void Flim::GameInitialize()
/// {
///		// Flim Window Device setup
///		this->setWindowName("Time and Input Demo");
///		this->setWidthHeight(800, 600);
///		this->SetClearColor(0.4f, 0.4f, 0.8f, 1.0f);
///
/// }
/// 	 
/// \endcode
////////////////////////////////////////////////////////////////////////////////////////////////////

void Flim::GameInitialize()
{
	// Flim Window Device setup
	this->setWindowName("WORLD OF TANKS (bootleg)");
	this->setWidthHeight(1400, 1400);
	this->SetClearColor(0.211f, 0.764f, 0.968f, 1.0f);
}


