#pragma once
#ifndef TransitionOnEnd_H
#define TransitionOnEnd_H

#include "CallbackCommand.h"

class Sound;

class TransitionOnEnd : public CallbackCommand
{
public:
	TransitionOnEnd();
	TransitionOnEnd(const char * name);
	TransitionOnEnd& operator=(const TransitionOnEnd&) = default;
	TransitionOnEnd(const TransitionOnEnd&) = default;
	~TransitionOnEnd();

	TransitionOnEnd(Sound* stop, Sound* start);

	void execute() override;
	TransitionOnEnd* clone() override;

private:
	char* waveName;

};

#endif