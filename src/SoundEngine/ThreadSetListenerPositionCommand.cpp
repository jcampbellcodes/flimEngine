#include "ThreadSetListenerPositionCommand.h"
#include "SoundManager3D.h"
void ThreadSetListenerPositionCommand::execute()
{
	SoundManager3D::UpdatePosition(cmd.listenerPosX, cmd.listenerPosY, cmd.listenerPosZ);
}
