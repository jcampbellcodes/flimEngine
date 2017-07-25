#include "PrintPriorityCommand.h"
#include "PriorityManager.h"

PrintPriorityCommand::PrintPriorityCommand()
{
}

void PrintPriorityCommand::execute()
{
	PriorityManager::PrintAll();
}
