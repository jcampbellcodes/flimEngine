#pragma once
#ifndef THREADCMDS_H
#define THREADCMDS_H

#include <string>
#include "BufferNode.h"
#include "flimFilter.h"
#include "flimReverb.h"
#include "SoundCallRegistry.h"
#include "AudioCommandType.h"

typedef enum ThreadCommandType
{
	// stored with their md5 hash values
	Play = 0xee8a5b16,
	Stop,
	Load,
	Pause,
	Pan = 0xc35b1997,
	Pitch = 0xada3d01f,
	Volume = 0x5b339ff6,
	CallbackSoundEnded = 0xb1b7a75f,
	Loop,
	CallbackSoundLoaded,
	CallbackSoundStarted,
	TerminateSoundEngine,
	CreatePlaylist,
	InitializeScript,
	LoadWave,
	TerminateFileThread,
	InitializeSound,
	SetEmitterPosition,
	SetListenerPosition,
	SetEmitterOrientation,
	SetListenerOrientation,
	ActivateFilter,
	DeactivateFilter,
	SetCutoff,
	SetReverbLevel,
	SetReverbDensity,
	SetReverbSize,
	SetReverbTime,
	SetReverbPredelay,
	SetReverbPreset
} ThreadCommandType;

enum class AudioEngineState
{
	ActiveAudioState,
	TerminateAudioState
};


struct ThreadCommand
{
	std::string scriptPath;
	std::string wavePath;
	SoundCallID id;

	AudioCommandType* type;
	AudioEngineState engineState;
	unsigned int handle;
	float listenerPosX;
	float listenerPosY;
	float listenerPosZ;
	float emitterPosX;
	float emitterPosY;
	float emitterPosZ;

	float listenerFrontX;
	float listenerFrontY;
	float listenerFrontZ;
	float emitterFrontX;
	float emitterFrontY;
	float emitterFrontZ;
	float listenerTopX;
	float listenerTopY;
	float listenerTopZ;
	float emitterTopX;
	float emitterTopY;
	float emitterTopZ;
	float filterCutoff;
	flimReverb reverbPreset;
	float pan;
	float pitch;
	float volume;
	float from;
	float to;
	float time;
	//reverb
	float reverbTime;
	float reverbDensity;
	float reverbSize;
	float reverbLevel;
	float reverbPredelay;

	FilterType filterType;
	BufferNode* bufferNode;
	void(*loadedCallback)(void);
	int triggerTime;
	bool loop;
	bool is3D;
};

#endif