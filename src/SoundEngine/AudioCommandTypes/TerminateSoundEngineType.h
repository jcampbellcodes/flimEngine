#ifndef TerminateSoundEngineTYPE
#define TerminateSoundEngineTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class TerminateSoundEngineType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const TerminateSoundEngineType type;
};

#endif