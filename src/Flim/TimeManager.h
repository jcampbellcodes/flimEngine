#pragma once
#ifndef FlimTimeMANAGER_H

#define FlimTimeMANAGER_H

#include "Flim.h"
#include "FreezeTime.h"

class FlimTime
{
private:
	FlimTime();
	FlimTime& operator=(const FlimTime&) = delete;
	FlimTime(const FlimTime&) = delete;
	~FlimTime();

	static FlimTime* instance;
	static FlimTime& Instance()
	{
		if (!instance)
		{
			instance = new FlimTime();
		}
		return *instance;
	}

	// members
	float gameTime;
	float frameTime;

	float previousFrameTime;
	float currentFrameTime;

	void privProcessTime();
	float privTotalTime();
	float privFrameTime();

	FreezeTime* FrzTime;

	void privTerminate();

	friend class Flim;
	static void ProcessTime()
	{
		Instance().privProcessTime();
	}

public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static float FlimTime::TotalFlimTime()
	///
	/// \brief	Total FlimTime the game has been running.
	/// \ingroup TOOLS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \code
	/// 	 
	/// 	 // Total runFlimTime of the game:
	/// 	 float totalFlimTime = FlimTime::TotalFlimTime();
	/// 	 
	/// \endcode
	///
	/// \return	The total FlimTime as a float.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static float TotalTime()
	{
		return Instance().privTotalTime();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static float FlimTime::FrameFlimTime()
	///
	/// \brief	Gets the FlimTime spent on each frame.
	/// \ingroup TOOLS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	/// 		
	/// \code
	/// 	 
	/// 	 // FlimTime between two successive frames
	/// 	 float frameFlimTime = FlimTime::FrameFlimTime();
	/// 	 
	/// \endcode
	/// 		
	///
	/// \return	A float value for the frame FlimTime.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static float FrameTime()
	{
		return Instance().privFrameTime();
	}
	
	static void Terminate()
	{
		Instance().privTerminate();
	}

};

#endif