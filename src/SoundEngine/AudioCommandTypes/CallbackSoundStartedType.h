#ifndef CallbackSoundStartedTYPE
#define CallbackSoundStartedTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class CallbackSoundStartedType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const CallbackSoundStartedType type;
};

#endif