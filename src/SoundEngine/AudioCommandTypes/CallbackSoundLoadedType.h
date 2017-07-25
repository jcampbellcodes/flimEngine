#ifndef CallbackSoundLoadedTYPE
#define CallbackSoundLoadedTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"
class ThreadCallbackSoundLoadedCommand;
class CallbackSoundLoadedType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static ThreadCallbackSoundLoadedCommand type;
};

#endif