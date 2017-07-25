#pragma once
#ifndef FLIMVERB_H
#define FLIMVERB_H


enum class flimReverb
{
	MOUNTAIN,
	CORRIDOR,
	PLATE,
	LARGE_ROOM,
	SMALL_ROOM
};

/*
class flimReverb
{
public:
	flimReverb() = default;
	flimReverb(const flimReverb&) = default;
	flimReverb& operator=(const flimReverb&) = default;
	~flimReverb() = default;



private:

	// mix percentage of echo signal to unaffected signal
	float wetDry; // 0 - 1

	// overall time before reverb reaches -60dB
	float reverbTime; // ms

	// ms before reverb starts after impact
	float preDelay; // ms

	// apparent size of the space
	float size; // 0 - 1

	// coloration of the reverb via room modes
	float density; // 0 - 1


};
*/

#endif