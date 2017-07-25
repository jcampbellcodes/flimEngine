#ifndef THREAD_HELPER_H
#define THREAD_HELPER_H

#include "WindowsWrapper.h"
#include <thread>

unsigned long long GetCurrentID();
void SetThreadName(std::thread &t0, char* threadName);
void SetMainThreadName(char* threadName);
const char * GetThreadName();

#endif