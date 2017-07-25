#ifndef SetListenerOrientationTYPE
#define SetListenerOrientationTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetListenerOrientationType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetListenerOrientationType type;
};

#endif