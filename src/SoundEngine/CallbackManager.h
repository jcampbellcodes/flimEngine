#pragma once
#ifndef CALLBACKMANAGER_H
#define CALLBACKMANAGER_H

#include "snd_err.h"
//#include <xaudio2.h>
#include "AutoXA2Include.h"
#include <map>
#include "SndExecutioner.h"


typedef enum CMDTYPES
{
	BUFFER_END,
	STREAM_END,
	VOICE_PROCESSING_PASS_END,
	VOICE_PROCESSING_PASS_START,
	BUFFER_START,
	LOOP_END,
	VOICE_ERROR,
	NO_TYPE
} CMDTYPES;

/*

todo........ change executioner to have processdeferredcommands and process instant commands
			 add these new executioners to the callback manager
			 in voice callback class, call the appropriate deferred and instance process methods
			 write submission methods for callback manager to add commands to the correct broker using the enum and... a switch?... or make it command pattern





Callback Manager
-------------------------CALLBACKMANAGER STUFF
-- singleton that has several registration brokers, one for each xaudio event
-- has a private callback method pointer that the voice manager has access to and uses to initialize voices
-- commands are submitted by audiosources to the callback manager (maybe with an enum as a parameter for the callback type), who
   adds them to the correct broker. Two submission methods: SubmitInstantCommand(Command*) and SubmitDeferredCommand(Command*)


------------------------SOUND&HANDLE STUFF
-- commands in the callback brokers stay for the entire life of a sound. it is a sound's responsibility to remove commands on its death



-------------------------BROKER STUFF
-- internally inside the xaudio2 callback object, the broker fires two methods : ProcessInstantCommands(); and ProcessDeferredCommands();
-- instant commands are execute()'d immediately, for commands that NEED to be instant, like a sample accurate transition
-- deferred commands are commands that you don't know how long they will take and will be detrimental in a blocking call
-- deferred commands sent to the timer class with a time of 0 so they will be process with the other commands in the timer process loop

*/

// responsible for loading itself
// containing attribute methods

class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	VoiceCallback() 
	{
		//DebugMsg::out("voice callback being created\n");
	};
	virtual ~VoiceCallback() 
	{
		//DebugMsg::out("voice callback being destroyed\n");
	};

	//Called when the voice has just finished playing a contiguous audio stream.
	virtual void __stdcall OnStreamEnd() = 0;
	virtual void __stdcall OnVoiceProcessingPassEnd() = 0;
	virtual void __stdcall OnVoiceProcessingPassStart(UINT32 SamplesRequired) = 0;

	virtual void __stdcall OnBufferEnd(void * pBufferContext) = 0;

	virtual void __stdcall OnBufferStart(void * pBufferContext) = 0;

	virtual void __stdcall OnLoopEnd(void * pBufferContext) = 0;

	virtual void __stdcall OnVoiceError(void * pBufferContext, HRESULT Error) = 0;
};

class CallbackMailbox : public VoiceCallback
{
public:

	//big four
	CallbackMailbox();
	~CallbackMailbox();
	CallbackMailbox& operator=(const CallbackMailbox&) = delete;
	CallbackMailbox(const CallbackMailbox&) = delete;

	snd_err SubmitCallback(CallbackCommand* cmd);

	VoiceCallback* GetCallbacks();

	snd_err Terminate();

private:

	const int NUM_VALID_CALLBACK_TYPES = 7;

	std::map<CMDTYPES, SoundExecutioner*> callbackBrokers;



	//callbacks
	//Called when the voice has just finished playing a contiguous audio stream.
	virtual void __stdcall OnStreamEnd();
	virtual void __stdcall OnVoiceProcessingPassEnd();

	virtual void __stdcall OnVoiceProcessingPassStart(UINT32 SamplesRequired);

	virtual void __stdcall OnBufferEnd(void * pBufferContext);

	virtual void __stdcall OnBufferStart(void * pBufferContext);

	virtual void __stdcall OnLoopEnd(void * pBufferContext);

	virtual void __stdcall OnVoiceError(void * pBufferContext, HRESULT Error);
};

#endif