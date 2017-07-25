#include "CreatePlaylistType.h"
#include "..\ThreadCreatePlaylistCommand.h"
AudioThreadCommand * CreatePlaylistType::visit()
{
	return new ThreadCreatePlaylistCommand();
}
