#pragma once
#ifndef SoundNode_H
#define SoundNode_H

// SoundNode base class
// next, prev

// classes inherit to store data members
#include "snd_err.h"
#include "AzulCore.h"

class Sound;

struct SoundData
{
	unsigned int md5;
	Sound* sound;
};

class SoundNode
{
public:
	SoundNode() = delete;
	SoundNode(unsigned int md5, Sound* _sound);
	~SoundNode();
	SoundNode(const SoundNode&) = default;
	SoundNode& operator=(const SoundNode&) = default;

	snd_err GetNext(SoundNode* out);
	snd_err SetNext(SoundNode* in);
	snd_err GetPrev(SoundNode * out);
	snd_err SetPrev(SoundNode * in);
	snd_err GetData(SoundData& out);
	snd_err SetData(SoundData& in);

private:
	SoundNode* next;
	SoundNode* prev;

	SoundData data;
	friend class SoundList;
	friend class SoundManager;

};


#endif