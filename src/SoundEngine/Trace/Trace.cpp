//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2016
// Optimized C++
//----------------------------------------------------------------------------- 
#include <stdio.h>
#include <assert.h>

// locals
#include "../WindowsWrapper.h"
#include "Trace.h"

void Trace::out(char* fmt, ...)
{
	Trace *pTrace = Trace::privGetInstance();
	assert(pTrace);
	
	va_list args;
	va_start(args, fmt);

		vsprintf_s(pTrace->privBuff, TraceBuffSize, fmt, args); 
		OutputDebugString( pTrace->privBuff );

	va_end(args);
}

Trace * Trace::privGetInstance()
{
	// This is where its actually stored (BSS section)
	static Trace helper;
	return &helper;
}