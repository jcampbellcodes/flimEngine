#pragma once
#ifndef VOICEFACTORY_H
#define VOICEFACTORY_H

//#include <xaudio2.h>
#include "AutoXA2Include.h"
#include "snd_err.h"
#include "CallbackManager.h"

#include <list>
#include <stack>
#include <set>

#define DEFAULT_NUM_VOICES 300


class Sound;
struct Track
{
	Track() = default;
	Track(const Track&) = default;
	Track& operator=(const Track&) = default;
	~Track();

	IXAudio2SourceVoice* voice = nullptr;
	CallbackMailbox* cbMailbox = nullptr;
	int startTime = 0;
	int lifetime = 0; // used later maybe for priority system
	int currentPriority = DEFAULT_NUM_VOICES;
	Sound* currentSound = nullptr;
};

class VoiceFactory
{
	// has a format object and pools voices created with that format
public:
	// no copying or creation without a format
	VoiceFactory() = delete;
	VoiceFactory(const VoiceFactory&) = delete;
	VoiceFactory& operator=(VoiceFactory&) = delete;

	VoiceFactory(WAVEFORMATEXTENSIBLE& wfx);

	// voice manager deletes all voice factories upon death
	// terminate factory, release/destroy voices
	~VoiceFactory();


	// user gets a voice
	snd_err GetVoice(Track*& out, int priority, Sound* sound);

	// user returns a voice to the pool
	snd_err ReturnVoice(Track*& in);


private:
	WAVEFORMATEXTENSIBLE& format;
	  
	// active voice pool
	std::list<Track*> activePool;

	// inactive voice stack
	std::set<Track*> inactivePool;

	snd_err AuditTracks(Track*& out, int priority, Sound* sound);


};

#endif