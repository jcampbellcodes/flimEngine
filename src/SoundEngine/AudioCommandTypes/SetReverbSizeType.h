#ifndef SetReverbSizeTYPE
#define SetReverbSizeTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetReverbSizeType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetReverbSizeType type;
};

#endif