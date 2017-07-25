#pragma once
#ifndef SoundManager3D_H
#define SoundManager3D_H

#include "AutoXA2Include.h"
#include "snd_err.h"
#include <x3daudio.h>
#include <list>

class Playlist;
// holds references to X3DAudio as well as the Listener
class SoundManager3D
{

private:

	SoundManager3D();

	SoundManager3D(const SoundManager3D&) = delete;
	const SoundManager3D& operator=(const SoundManager3D&) = delete;
	~SoundManager3D();

	static SoundManager3D* instance;
	static SoundManager3D& Instance()
	{
		if (!instance)
		{
			instance = new SoundManager3D();
		}
		return *instance;
	}

	X3DAUDIO_HANDLE x3DAudio;

	X3DAUDIO_LISTENER* listener;

	X3DAUDIO_VECTOR pos;
	X3DAUDIO_VECTOR front;
	X3DAUDIO_VECTOR top;

	snd_err privUpdatePosition(float x, float y, float z);
	snd_err privUpdateOrientation(float xF, float yF, float zF, float xU, float yU, float zU);
	snd_err SoundManager3D::privCalculate(X3DAUDIO_EMITTER *& emit, X3DAUDIO_DSP_SETTINGS*& dspSettings);

	snd_err privUpdate3DAudio();
	snd_err privRegister3DSound(Playlist*);
	snd_err privDeregister3DSound(Playlist*);
	std::list<Playlist*> registeredSounds;


	

public:

	// update listener position method, takes in a vector
	static snd_err UpdatePosition(float x, float y, float z)
	{
		return Instance().privUpdatePosition(x, y, z);
	}

	// update listener position method, takes in a vector
	static snd_err UpdateOrientation(float xF, float yF, float zF, float xU, float yU, float zU)
	{
		return Instance().privUpdateOrientation(xF, yF, zF, xU, yU, zU);
	}

	// calculate; pass in pointer to emitter, called by requesting playlists
	static snd_err CalculateEmitterValues(X3DAUDIO_EMITTER *& emit, X3DAUDIO_DSP_SETTINGS*& dspSettings)
	{
		return Instance().privCalculate(emit, dspSettings);
	}

	static snd_err Update3DAudio()
	{
		return Instance().privUpdate3DAudio();
	}

	static snd_err Register3DSound(Playlist* p)
	{
		return Instance().privRegister3DSound(p);
	}
	static snd_err Deregister3DSound(Playlist* p)
	{
		return Instance().privDeregister3DSound(p);
	}

};




#endif