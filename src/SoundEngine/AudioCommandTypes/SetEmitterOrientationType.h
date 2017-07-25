#ifndef SetEmitterOrientationTYPE
#define SetEmitterOrientationTYPE
#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetEmitterOrientationType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetEmitterOrientationType type;
};

#endif