#ifndef SetReverbDensityTYPE
#define SetReverbDensityTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetReverbDensityType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetReverbDensityType type;
};

#endif