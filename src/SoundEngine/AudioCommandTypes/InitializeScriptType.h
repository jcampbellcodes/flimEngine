#ifndef InitializeScriptTYPE
#define InitializeScriptTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class InitializeScriptType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const InitializeScriptType type;
};

#endif