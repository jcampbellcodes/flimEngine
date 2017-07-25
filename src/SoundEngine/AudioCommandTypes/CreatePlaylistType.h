#ifndef CreatePlaylistTYPE
#define CreatePlaylistTYPE

#include "..\AudioThreadCommand.h"
#include "..\AudioCommandType.h"

class CreatePlaylistType : public AudioCommandType
{
public:
	AudioThreadCommand* visit() override;
	static const CreatePlaylistType type;
};

#endif