#pragma once
#ifndef SoundList_H
#define SoundList_H

#include "snd_err.h"
#include "SoundNode.h"


class SoundNode;
class BufferSoundNode;

// Derive from SoundList to change SoundNode types

class SoundList
{
public:
	// big four
	SoundList();
	~SoundList();
	SoundList(const SoundList&);
	SoundList& operator=(const SoundList&);

	// if you have the SoundNode
	snd_err Add(SoundNode* in);
	snd_err Remove(SoundNode* in);

	// if you don't
	snd_err Add(unsigned int md5, Sound* snd);
	snd_err Remove(unsigned int md5);
	snd_err Remove(Sound* snd);

	snd_err Find(SoundNode*& out, unsigned int md5);
	snd_err Find(SoundNode*& out, Sound* snd);

	snd_err Print();
			
private:
	SoundNode* head;

};

#endif // !SoundList_H
