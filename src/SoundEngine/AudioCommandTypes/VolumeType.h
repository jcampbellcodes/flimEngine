#ifndef VolumeTYPE
#define VolumeTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class VolumeType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const VolumeType type;
};

#endif