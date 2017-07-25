#include "FreezeTime.h"
#include "Flim.h"
#include "TimeManager.h"

FreezeTime::FreezeTime()
{
	freeze_mode_active = false;
	totalFrozenTime = 0;
}

float FreezeTime::GetTimeInSeconds(float sys_time)
{
	// This is the correct value to return on this frame
	float activeGameTime = sys_time - totalFrozenTime;

	// Now we test whether we should enter freeze-frame mode:
	// Either we activated the freeze-time mode or 
	// we are returning after a single frame request
	if (HackedKeyRelease(FREEZE_KEY) || freeze_mode_active)
	{	
		//DebugMsg::out("FREEZE FRAME at %f\n", activeGameTime);
		totalFrozenTime = WaitAndReturnFrozenTime( activeGameTime);
	}

	return activeGameTime;
}

float FreezeTime::WaitAndReturnFrozenTime(float activetime)
{
	freeze_mode_active = true;	// Freeze time 
	bool single_frame = false;	// No single frame request yet

	// Loop until freeze-time is cancelled or a single frame is requested
	while (freeze_mode_active && !single_frame)
	{
		if (HackedKeyRelease(FREEZE_KEY))
		{
			freeze_mode_active = false;		// Cancel both freeze-time modes
			single_frame = false;
		}
		else if (HackedKeyRelease(SINGLE_FRAME_KEY))
		{
			single_frame = true;	// Request a single frame
		}

		glfwPollEvents();  // We must get GLFW to rescan the keyboard
	}

	// This is the cumulative time we were in freeze-frame 
	return FlimTime::TotalTime() - activetime;
}

// Helper function to detect a key press-and-release event
// Very hacky: The loop to wait for a release is resource intensive.
// Only good because we are freeze-framing the engine.
bool FreezeTime::HackedKeyRelease(AZUL_KEY k)
{
	if (Keyboard::GetKeyState(k)) // Is the key pressed?
	{		
		while (Keyboard::GetKeyState(k)) // then poll keyboard until k is released
		{
			glfwWaitEvents(); // Sleep until something happens (typically, k is released)
		}
		return true;  // Key k was pressed and released.
	}
	else
		return false; // Key k was not pressed
}

