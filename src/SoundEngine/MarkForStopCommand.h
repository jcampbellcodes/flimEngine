#pragma once
#ifndef MARKFORStopCOMMAND_H
#define MARKFORStopCOMMAND_H

#include "AudioCommand.h"
class SoundCall;

class MarkForStopCommand : public AudioCommand
{
public:
	MarkForStopCommand() = delete;
	MarkForStopCommand(const MarkForStopCommand&) = default;
	MarkForStopCommand& operator=(const MarkForStopCommand&) = default;
	~MarkForStopCommand() = default;

	MarkForStopCommand(SoundCall* snd);

	void execute() override;

	MarkForStopCommand* clone() { return nullptr; };

private:
	SoundCall* attemptToStop;


};

#endif