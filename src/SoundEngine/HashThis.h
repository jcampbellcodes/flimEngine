#pragma once
#ifndef HASHTHIS_H
#define HASHTHIS_H

//#include <xaudio2.h>
#include "AutoXA2Include.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \fn	unsigned int HashThis(const char* input);
///
/// \brief	Hashes a string with MD5 for use as a key.
///
/// \author	Jack Campbell
/// \date	6/1/2017
///
/// \param	input	String input to be hashed
///
/// \return	Unsigned int, the result of MD5 hash.
////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int HashThis(const char* input);

unsigned int HashThis(WAVEFORMATEXTENSIBLE& wfx);

#endif