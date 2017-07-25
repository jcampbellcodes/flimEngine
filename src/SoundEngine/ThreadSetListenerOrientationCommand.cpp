#include "ThreadSetListenerOrientationCommand.h"
#include "SoundManager3D.h"
void ThreadSetListenerOrientationCommand::execute()
{
	SoundManager3D::UpdateOrientation(cmd.listenerFrontX, cmd.listenerFrontY, cmd.listenerFrontZ, cmd.listenerTopX, cmd.listenerTopY, cmd.listenerTopZ);

}
