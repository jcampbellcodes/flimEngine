#include "Executioner.h"
#include "Command.h"

void Executioner::addCommand(Command * in)
{
	cmdList.push_back(in);
}

void Executioner::ExecuteCommands()
{
	std::list<Command*>::iterator iter = cmdList.begin();

	while (iter != cmdList.end())
	{
		(*iter)->execute();
		iter++;
	}
	cmdList.clear();
}
