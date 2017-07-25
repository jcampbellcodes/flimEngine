#ifndef LoadTYPE
#define LoadTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class LoadType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const LoadType type;
};

#endif