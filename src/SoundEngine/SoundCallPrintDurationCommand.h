#pragma once
#ifndef PRINTDURATION_H
#define PRINTDURATION_H
#include "AudioCommand.h"
#include <string>

class SoundCall;


class SoundCallPrintDuration : public AudioCommand
{
public:
	SoundCallPrintDuration() = delete;
	SoundCallPrintDuration(const SoundCallPrintDuration&) = default;
	SoundCallPrintDuration& operator=(const SoundCallPrintDuration&) = default;
	~SoundCallPrintDuration() = default;

	SoundCallPrintDuration(SoundCall* snd, const char* waveName);

	void execute() override;

	SoundCallPrintDuration* clone() { return nullptr; }

private:
	SoundCall* soundCall;
	const char* name;

};

#endif