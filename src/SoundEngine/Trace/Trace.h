//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2016
// Optimized C++
//----------------------------------------------------------------------------- 

#ifndef DEBUG_OUTPUT_H
#define DEBUG_OUTPUT_H

#define TraceBuffSize 256

// NOTE: you need to set your project settings
//       Character Set -> Use Multi-Byte Character Set

// Singleton helper class
class Trace
{
public:
	// displays a printf to the output window
	static void out(char* fmt, ...);

	// Big four
	Trace() = default;
	Trace(const Trace &) = default;
	Trace & operator = (const Trace &) = default;
	~Trace() = default;

private:
	static Trace *privGetInstance();
	char privBuff[TraceBuffSize];
};


#endif