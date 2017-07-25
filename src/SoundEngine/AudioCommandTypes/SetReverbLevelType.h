#ifndef SetReverbLevelTYPE
#define SetReverbLevelTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetReverbLevelType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetReverbLevelType type;
};

#endif