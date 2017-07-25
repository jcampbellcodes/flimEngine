#pragma once
#ifndef MARKFORPLAYCOMMAND_H
#define MARKFORPLAYCOMMAND_H

#include "AudioCommand.h"
class SoundCall;

class MarkForPlayCommand : public AudioCommand
{
public:
	MarkForPlayCommand() = delete;
	MarkForPlayCommand(const MarkForPlayCommand&) = default;
	MarkForPlayCommand& operator=(const MarkForPlayCommand&) = default;
	~MarkForPlayCommand() = default;

	MarkForPlayCommand(SoundCall* snd, int& index);

	void execute() override;

	MarkForPlayCommand* clone() { return nullptr; };

private:
	int& priorityIndex;
	SoundCall* attemptToPlay;


};

#endif