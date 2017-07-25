#ifndef DEBUG_OUT_H
#define DEBUG_OUT_H

	#include <Windows.h>
	#include <stdio.h>
#include <stdarg.h>

class DebugMsg
{
private:
	static char DebugBuff[256];

public:
	static void out( char* A, ...)
	{
		va_list args;
		va_start(args, A);
		vsprintf_s(DebugBuff, A, args);
		OutputDebugString(DebugBuff);
	};
};



#endif