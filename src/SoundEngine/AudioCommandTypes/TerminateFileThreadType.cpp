#include "TerminateFileThreadType.h"
#include "..\ThreadTerminateFileThreadCommand.h"
AudioThreadCommand * TerminateFileThreadType::visit()
{
	return new ThreadTerminateFileThreadCommand();
}
