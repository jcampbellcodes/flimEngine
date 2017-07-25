#ifndef CallbackSoundLoadedTYPE
#define CallbackSoundLoadedTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class CallbackSoundLoadedType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const CallbackSoundLoadedType type;
};

#endif