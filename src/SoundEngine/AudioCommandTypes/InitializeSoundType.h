#ifndef InitializeSoundTYPE
#define InitializeSoundTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class InitializeSoundType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const InitializeSoundType type;
};

#endif