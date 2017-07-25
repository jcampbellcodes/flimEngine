#ifndef SND_MANAGER_H
#define SND_MANAGER_H

//#define _USE_TRACE_NEW

#if defined(_DEBUG) && defined(_USE_TRACE_NEW)
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif


#include "CircularData.h"
#include "AudioCommand.h"
#include "snd_err.h"
#include "SoundCall.h"
#include "SoundCallRegistry.h"

#include <map>

class SoundEngine
{
public:
	// Defaults
	SoundEngine(const SoundEngine &) = delete;
	const SoundEngine &operator = (const SoundEngine &) = delete;


	// Public methods:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::Create()
	///
	/// \brief	Creates the SoundEngine.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err Create()
	{
		return Instance().privCreate();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::Update()
	///
	/// \brief	Updates this sound engine, processing commands.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err Update()
	{
		return Instance().privUpdate();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::SendData(ThreadCommand val)
	///
	/// \brief	Sends a command to the audio thread.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	val	The value.
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err SendData(ThreadCommand val)
	{
		return Instance().privSendData(val);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::SendDataA2G(ThreadCommand val)
	///
	/// \brief	Sends a command from audio thread to game.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param	val	The value.
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err SendDataA2G(ThreadCommand val)
	{
		return Instance().privSendDataA2G(val);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static CircularData SoundEngine::*GetG2ABuff()
	///
	/// \brief	Gets g 2 a buffer.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	Null if it fails, else the g 2 a buffer.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static CircularData *GetG2ABuff()
	{
		return Instance().privGetG2ABuff();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static CircularData SoundEngine::*GetA2GBuff()
	///
	/// \brief	Gets a 2 g buffer.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	Null if it fails, else a 2 g buffer.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static CircularData *GetA2GBuff()
	{
		return Instance().privGetA2GBuff();
	}


	// Manager pool related

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::CreateSoundCall(SoundCall*&in, SoundCallID id, bool _3D)
	///
	/// \brief	Creates sound call.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in 	[in,out] If non-null, the in.
	/// \param 		   	id 	The identifier.
	/// \param 		   	_3D	True to 3D.
	///
	/// \return	The new sound call.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err CreateSoundCall(SoundCall*&in, SoundCallID id, bool _3D)
	{
		return Instance().privCreateSoundCall(in, id, _3D);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::CreateSoundCall(SoundCall*&in, SoundCallID id, int priority)
	///
	/// \brief	Creates sound call.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in			[in,out] If non-null, the in.
	/// \param 		   	id			The identifier.
	/// \param 		   	priority	The priority.
	///
	/// \return	The new sound call.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err CreateSoundCall(SoundCall*&in, SoundCallID id, int priority)
	{
		return Instance().privCreateSoundCall(in, id, priority);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::ReturnSoundCall(SoundCall* in)
	///
	/// \brief	Returns sound call.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	in	If non-null, the in.
	///
	/// \return	The sound call.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err ReturnSoundCall(SoundCall* in)
	{
		return Instance().privReturnSoundCall(in);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::FindSoundCall(SoundCall*& out, unsigned int handle)
	///
	/// \brief	Searches for the first sound call.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param [in,out]	out   	[in,out] If non-null, the out.
	/// \param 		   	handle	The handle.
	///
	/// \return	The found sound call.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err FindSoundCall(SoundCall*& out, unsigned int handle)
	{
		return Instance().privFindSoundCall(out, handle);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::Terminate()
	///
	/// \brief	Gets the terminate.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err Terminate()
	{
		return Instance().privTerminate();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::LoadScript(std::string path, SoundCallID id, void(*cb)(void) = nullptr)
	///
	/// \brief	Loads a script.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param 		   	path	Full pathname of the file.
	/// \param 		   	id  	The identifier.
	/// \param [in,out]	cb  	(Optional) If non-null, the cb.
	///
	/// \return	The script.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err LoadScript(std::string path, SoundCallID id, void(*cb)(void) = nullptr)
	{
		return Instance().privLoadScript(path, id, cb);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err SoundEngine::LoadSound(std::string path, SoundCallID id, void(*cb)(void) = nullptr)
	///
	/// \brief	Loads a sound.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///
	/// \param 		   	path	Full pathname of the file.
	/// \param 		   	id  	The identifier.
	/// \param [in,out]	cb  	(Optional) If non-null, the cb.
	///
	/// \return	The sound.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err LoadSound(std::string path, SoundCallID id, void(*cb)(void) = nullptr)
	{
		return Instance().privLoadSound(path, id, cb);
	}

private:
	static SoundEngine *instance;
	static SoundEngine& Instance()
	{
		if (!instance)
		{
			instance = new SoundEngine();
		}
		return *instance;
	}

	SoundEngine();
	~SoundEngine(); // probably should die

	snd_err privCreateSoundCall(SoundCall *& in, SoundCallID id, int priority);

	CircularData *pG2ABuff;  // Game to Audio
	CircularData *pA2GBuff; // Audio to Game

	// private methods
	snd_err privUpdate();
	snd_err privSendData(ThreadCommand val);
	snd_err privSendDataA2G(ThreadCommand val);
	snd_err privCreate();
	snd_err privTerminate();

	// manager pool
	snd_err privCreateSoundCall(SoundCall*&in, SoundCallID id, bool _3D);
	snd_err privReturnSoundCall(SoundCall* in); // do we need it?
	snd_err privFindSoundCall(SoundCall*& out, unsigned int handle);

	snd_err privLoadScript(std::string path, SoundCallID id, void(*cb)(void));
	snd_err privLoadSound(std::string path, SoundCallID id, void(*cb)(void));

	snd_err privLoadScript(const char* path, SoundCallID id, void(*cb)(void));

	std::map<unsigned int, SoundCall*> activeSoundCalls;

	CircularData *privGetG2ABuff();
	CircularData *privGetA2GBuff();

	std::thread audioThread;


};
#endif
