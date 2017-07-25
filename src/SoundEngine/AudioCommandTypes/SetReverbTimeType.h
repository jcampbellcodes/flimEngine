#ifndef SetReverbTimeTYPE
#define SetReverbTimeTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetReverbTimeType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetReverbTimeType type;
};

#endif