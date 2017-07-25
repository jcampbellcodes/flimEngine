#include "HashThis.h"
#include "md5.h"
//#include <xaudio2.h>
#include "AutoXA2Include.h"
//#include <xaudio2.h>
#define MAX_NAME_SIZE 32

unsigned int HashThis(const char* input)
{
	// usually hash inupt to MD5, create tuples

	unsigned char hashThis[MAX_NAME_SIZE] = { 0 };
	unsigned char i = input[0];
	unsigned int iterator = 0;
	while (i != '\0')
	{
		hashThis[iterator] = input[iterator];
		i = input[iterator];
		iterator++;
	}

	MD5Output out;
	MD5Buffer(hashThis, MAX_NAME_SIZE, out);

	// create a reduced hash:
	unsigned int md5;
	md5 = out.dWord_0 ^ out.dWord_1 ^ out.dWord_2 ^ out.dWord_3;
	return md5;
}

// similar, but a convenience for hashing wave format data
unsigned int HashThis(WAVEFORMATEXTENSIBLE& wfx)
{
	unsigned char hashThis[sizeof(wfx)] = { 0 };
	unsigned char* i = reinterpret_cast<unsigned char*>((&wfx));
	unsigned int iterator = 0;
	while (iterator < sizeof(wfx))
	{
		hashThis[iterator] = *i;
		i++;
		iterator++;
	}

	MD5Output out;
	MD5Buffer(hashThis, MAX_NAME_SIZE, out);

	// create a reduced hash:
	unsigned int md5;
	md5 = out.dWord_0 ^ out.dWord_1 ^ out.dWord_2 ^ out.dWord_3;
	return md5;
}
