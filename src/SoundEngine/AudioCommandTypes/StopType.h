#ifndef StopTYPE
#define StopTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class StopType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const StopType type;
};

#endif