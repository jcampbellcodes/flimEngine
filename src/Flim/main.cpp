
#include "Flim.h"

int CALLBACK WinMain(HINSTANCE , HINSTANCE ,  LPSTR , int)                  
{          

	// start the game
	Flim::Run();                                  

#ifdef _USE_TRACE_NEW
	_CrtDumpMemoryLeaks();
#endif

	return 0;                                       
}

