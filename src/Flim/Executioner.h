#pragma once
#ifndef EXECUTIONER_H
#define EXECUTIONER_H

#include <list>
#include "Command.h"
#include "AzulCore.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	Executioner
///
/// \brief	An object that accepts commands and fires them all off when asked.
///
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class Executioner
{
public:
	Executioner() = default;
	~Executioner() {
		//DebugMsg::out("Executioner Cleaned\n");
	};
	Executioner(const Executioner&) = default;
	Executioner& operator=(const Executioner&) = default;

	void addCommand(Command* in);
	void ExecuteCommands();

private:
	std::list<Command*> cmdList;


};

#endif