#ifndef SetReverbPresetTYPE
#define SetReverbPresetTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetReverbPresetType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetReverbPresetType type;
};

#endif