#ifndef PitchTYPE
#define PitchTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class PitchType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const PitchType type;
};

#endif