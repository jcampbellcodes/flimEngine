#include "ThreadCallbackSoundEndedCommand.h"
#include "CallbackSoundEndedCommand.h"
void ThreadCallbackSoundEndedCommand::execute()
{
	CallbackSoundEndedCommand endedcb;
	endedcb.SetContext(cmd.id, cmd.handle);
	endedcb.execute();
}
