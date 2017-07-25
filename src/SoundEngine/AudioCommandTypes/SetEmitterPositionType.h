#ifndef SetEmitterPositionTYPE
#define SetEmitterPositionTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetEmitterPositionType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetEmitterPositionType type;
};

#endif