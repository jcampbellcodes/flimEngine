#pragma once
#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "snd_err.h"
#include "SoundCallRegistry.h"
#include "Timer.h"
#include "flimFilter.h"
#include <list>
#include <map>
#include "flimReverb.h"
class Channel;
class Sound;
class AudioCommand;
class CallbackCommand;
class InternalSoundEnded;

struct CmdWithTime
{
	~CmdWithTime();

	int time;
	AudioCommand* cmd;
};

class Playlist
{
public:
	// big four
	Playlist() = delete;
	//Playlist(SoundCallID id, unsigned int instance);
	Playlist(const Playlist&);
	Playlist& operator=(const Playlist&);
	Playlist(SoundCallID _id, unsigned int instance, bool _3D);
	~Playlist();

	// occupy all sounds
	snd_err PrepareToPlay();

	// add sound -- doesn't make sense if can't be referred to by script. needs to have an identifier
	//snd_err AddSound(Sound* snd);

	// add sound by name
	snd_err AddSound(const char* snd);

	// add sound by hash
	snd_err AddSound(unsigned int snd);

	// add command
	snd_err AddCommand(AudioCommand* cmd, int time, unsigned int id);


	// add callback command
	snd_err AddCommand(CallbackCommand* cmd, int time, unsigned int id1, unsigned int id2);

	// tell game side we are done
	snd_err SendCallbackSoundEnded();

	snd_err setEmitterPos(float x, float y, float z);
	snd_err setEmitterOrientation(float xF, float yF, float zF, float xU, float yU, float zU);

	// internal housekeeping
	snd_err SoundEnded();

	// public API
	snd_err Play(bool toLoop = false);
	snd_err Stop();
	snd_err Pause();
	snd_err Pan(float pan);
	snd_err Loop(bool toLoop);
	snd_err Pitch(float pitch);
	snd_err Volume(float volume);


	// filter stuff -- filter always enabled until you disable it
	snd_err ActivateFilter(FilterType type);
	snd_err DeactivateFilter(FilterType type);

	snd_err SetCutoff(float cutoff);
	snd_err GetCutoff(float& cutoff);

	// reverb
	
	// reverb
	snd_err SetReverbLevel(float level);
	snd_err SetReverbTime(float time);
	snd_err SetReverbPreDelay(float time);
	snd_err SetReverbSize(float size);
	snd_err SetReverbDensity(float density);

	snd_err SetReverbPreset(flimReverb reverb);

	Channel* getChannel() { return channel; };

	bool IsPlaying();

	unsigned int GetInstanceNumber();

private:
	bool is3D;
	snd_err AddCommand(AudioCommand * cmd, int time);
	// list of commands to add to timeline
	std::list<CmdWithTime*> commands;
	// list of Sounds to get
	std::map<unsigned int, Sound*> sounds;
	Channel* channel;
	InternalSoundEnded* internalSoundEnded;
	bool soundsLoaded;
	bool isPlaying;
	// ID from enum
	SoundCallID id;
	Timer startTime;
	bool loop;
	// instance identifier -> soundcall handle hashed
	unsigned int instanceNumber;
	int numSoundsPlaying;

};

#endif