#ifndef PanTYPE
#define PanTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class PanType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const PanType type;
};

#endif