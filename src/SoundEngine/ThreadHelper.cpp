#include "WindowsWrapper.h"
#include <iostream>
#include <thread>
#include <sstream> 

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
	DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)


unsigned long long GetCurrentID()
{
	// Get the string ID in an Integer form
	std::stringstream ss;


	ss << std::this_thread::get_id();
	uint64_t id = std::stoull(ss.str());

	return id;
}

const char * GetThreadName()
{
	// ??? 

	// I think we need to create a shadow structure, 
	// since we set it... we can get shadow copy it.

	// It doesn't exist in reality, only in Debugger IDE land
	return 0;
}

void SetThreadName(std::thread &t0, char* threadName)
{

	DWORD threadId = ::GetThreadId(static_cast<HANDLE>(t0.native_handle()));

	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = threadId;
	info.dwFlags = 0;

	__try
	{
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

void SetMainThreadName( char* threadName)
{
	DWORD threadId = ::GetThreadId( GetCurrentThread() );

	THREADNAME_INFO info;
	info.dwType = 0x1000;
	info.szName = threadName;
	info.dwThreadID = threadId;
	info.dwFlags = 0;

	__try
	{
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
	}
}