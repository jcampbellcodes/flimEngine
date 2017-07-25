#ifndef ActivateFilterTYPE
#define ActivateFilterTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class ThreadActivateFilterCommand;

class ActivateFilterType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static ThreadActivateFilterCommand type;
};

#endif