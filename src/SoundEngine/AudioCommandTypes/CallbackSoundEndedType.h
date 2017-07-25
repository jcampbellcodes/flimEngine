#ifndef CallbackSoundEndedTYPE
#define CallbackSoundEndedTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class ThreadCallbackSoundEndedCommand;

class CallbackSoundEndedType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static ThreadCallbackSoundEndedCommand type;
};

#endif