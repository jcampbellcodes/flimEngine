#ifndef SetReverbPredelayTYPE
#define SetReverbPredelayTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetReverbPredelayType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetReverbPredelayType type;
};

#endif