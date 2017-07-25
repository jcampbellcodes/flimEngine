#ifndef DeactivateFilterTYPE
#define DeactivateFilterTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class DeactivateFilterType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const DeactivateFilterType type;
};

#endif