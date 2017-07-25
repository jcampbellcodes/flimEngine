#pragma once
#ifndef PRINTPRIORITYCOMMAND_H
#define PRINTPRIORITYCOMMAND_H

#include "AudioCommand.h"
class SoundCall;

class PrintPriorityCommand : public AudioCommand
{
public:
	PrintPriorityCommand();
	PrintPriorityCommand(const PrintPriorityCommand&) = default;
	PrintPriorityCommand& operator=(const PrintPriorityCommand&) = default;
	~PrintPriorityCommand() = default;

	void execute() override;

	PrintPriorityCommand* clone() { return nullptr; };

private:

};

#endif