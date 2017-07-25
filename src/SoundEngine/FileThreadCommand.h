#pragma once
#ifndef FILETHREADCOMMAND_H
#define FILETHREADCOMMAND_H

#include "BufferNode.h"

struct FileThreadCommand
{
	BufferNode* node;
	const char* pathToWAVE;
};

typedef enum FLIM_FILETHREAD_COMMAND_TYPE
{
	LoadWave,
	TerminateFileThread
} FLIM_FILETHREAD_COMMAND_TYPE;

#endif