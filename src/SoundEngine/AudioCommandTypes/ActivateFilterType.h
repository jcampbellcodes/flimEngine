#ifndef ActivateFilterTYPE
#define ActivateFilterTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class ActivateFilterType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const ThreadActivateFilterCommand type;
};

#endif