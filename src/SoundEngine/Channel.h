#pragma once
#ifndef Channel_H
#define Channel_H
#include "snd_err.h"
#include "AzulCore.h"

#include "Handle.h"
#include "HandleManager.h"
#include "VoiceFactory.h"
#include <x3daudio.h>
#include <xaudio2fx.h>

//#include <xaudio2.h>
#include "AutoXA2Include.h"
#include <stdio.h>
#include <string>
#include "flimReverb.h"
#include "flimFilter.h"

class CallbackCommand;
class Sound;

class Channel
{
public:
	//big four
	Channel() = delete;
	//Channel(WAVEFORMATEXTENSIBLE _wfx, XAUDIO2_BUFFER* _buffer, Voice* _sourceVoice);
	Channel(IXAudio2SubmixVoice* submix, IXAudio2SubmixVoice* reverb = nullptr);

	Channel(const Channel& in) = default;
	Channel& operator=(const Channel& in) = default;
	~Channel();

	// public API
	snd_err Pan(float pan);
	snd_err setEmitterPos(float x, float y, float z);
	snd_err setEmitterOrientation(float xF, float yF, float zF, float xU, float yU, float zU);
	snd_err Volume(float volume);

	// filter stuff -- filter always enabled until you disable it
	snd_err ActivateFilter(FilterType type);
	snd_err DeactivateFilter(FilterType type);

	snd_err SetCutoff(float cutoff);
	snd_err GetCutoff(float& cutoff);

	// reverb
	snd_err SetReverbLevel(float level);
	snd_err SetReverbTime(float time);
	snd_err SetReverbPreDelay(float time);
	snd_err SetReverbSize(float size);
	snd_err SetReverbDensity(float density);
	snd_err SetReverbPreset(flimReverb reverb);

	X3DAUDIO_VECTOR GetPos() const { return vPosition; }
	X3DAUDIO_EMITTER* GetEmitter() const { return emitter; }
	X3DAUDIO_DSP_SETTINGS* GetDSPSettings() const { return dspSettings; }

	// filter
	IXAudio2SubmixVoice* GetSubmixVoice() const;

private:
	friend class Sound;


	IXAudio2SubmixVoice* voice;
	IXAudio2SubmixVoice* reverbReturn;
	XAUDIO2_FILTER_PARAMETERS* params;
	XAUDIO2FX_REVERB_PARAMETERS reverbParams;

	X3DAUDIO_VECTOR vPosition;
	X3DAUDIO_EMITTER* emitter;
	X3DAUDIO_DSP_SETTINGS* dspSettings;



	float cutoffFrequency;

	// reverb
};
#endif