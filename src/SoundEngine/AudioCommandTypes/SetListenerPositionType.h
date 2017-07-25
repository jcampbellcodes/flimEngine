#ifndef SetListenerPositionTYPE
#define SetListenerPositionTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetListenerPositionType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetListenerPositionType type;
};

#endif