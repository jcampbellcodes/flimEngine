#ifndef SetCutoffTYPE
#define SetCutoffTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class SetCutoffType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const SetCutoffType type;
};

#endif