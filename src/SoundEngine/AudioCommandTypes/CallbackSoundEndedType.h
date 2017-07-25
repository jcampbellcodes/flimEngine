#ifndef CallbackSoundEndedTYPE
#define CallbackSoundEndedTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class CallbackSoundEndedType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const CallbackSoundEndedType type;
};

#endif