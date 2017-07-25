#ifndef TerminateFileThreadTYPE
#define TerminateFileThreadTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class TerminateFileThreadType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const TerminateFileThreadType type;
};

#endif