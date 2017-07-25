#ifndef LoopTYPE
#define LoopTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class LoopType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const LoopType type;
};

#endif