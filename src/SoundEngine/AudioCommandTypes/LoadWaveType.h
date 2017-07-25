#ifndef LoadWaveTYPE
#define LoadWaveTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class LoadWaveType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const LoadWaveType type;
};

#endif