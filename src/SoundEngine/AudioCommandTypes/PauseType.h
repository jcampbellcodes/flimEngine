#ifndef PauseTYPE
#define PauseTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class PauseType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const PauseType type;
};

#endif