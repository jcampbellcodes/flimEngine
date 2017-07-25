#pragma once
#ifndef AUDIOCOMMANDTYPE
#define AUDIOCOMMANDTYPE

class AudioThreadCommand;

class AudioCommandType
{
public:
	virtual AudioThreadCommand* visit() = 0;
};

#endif