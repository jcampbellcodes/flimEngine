#ifndef LIBRARY_SETUP_H
#define LIBRARY_SETUP_H

	#ifdef WIN32
		#pragma once
		#define _CRT_SECURE_NO_WARNINGS 1

		#define WIN32_LEAN_AND_MEAN 1
		#include <Windows.h>

		#ifdef _DEBUG
			#ifdef _WIN64
				#pragma comment (lib, "GLFW_d64.lib")
				#ifndef IN_SB6_LIB
					#pragma comment (lib, "sb6_d64.lib")
				#endif
			#else
				//#pragma comment (lib, "GLFW_d32.lib")
				#pragma comment (lib, "GLFW_Debug.lib")
				#ifndef IN_SB6_LIB
					#pragma comment (lib, "sb6_Debug.lib")
				#endif
			#endif
		#else
			#ifdef _WIN64
				#pragma comment (lib, "GLFW_r64.lib")
				#ifndef IN_SB6_LIB
					#pragma comment (lib, "sb6_r64.lib")
				#endif
			#else
				#pragma comment (lib, "GLFW_r32.lib")
				#ifndef IN_SB6_LIB
					#pragma comment (lib, "sb6_r32.lib")
				#endif
			#endif
		#endif

		#pragma comment (lib, "OpenGL32.lib")
	#endif

#endif