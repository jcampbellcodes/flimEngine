#include "FlimListener.h"
#include "SoundEngine.h"
#include "ThreadCommands.h"
#include "SoundManager.h"
#include "AudioCommandTypes\SetListenerOrientationType.h"
#include "AudioCommandTypes\SetListenerPositionType.h"
FlimListener* FlimListener::instance = nullptr;

FlimListener::FlimListener()
{
	this->position = Vect(0, 0, 0);
}

const Vect & FlimListener::privGetPosition()
{
	return this->position;
}

snd_err FlimListener::privSetPosiion(float x, float y, float z)
{
	// reset position
	this->position.set(x, y, z);

	// send thread command
	ThreadCommand cmd;
	cmd.type = new SetListenerPositionType();
	cmd.listenerPosX = x;
	cmd.listenerPosY = y;
	cmd.listenerPosZ = z;

	CircularData* pOut = SoundEngine::GetG2ABuff();

	pOut->PushBack(cmd);

	return snd_err::OK;
}

snd_err FlimListener::privUpdateOrientation(float xF, float yF, float zF, float xU, float yU, float zU)
{
	// reset position
	//this->position.set(x, y, z);

	// send thread command
	ThreadCommand cmd;
	cmd.type = new SetListenerOrientationType();
	cmd.listenerFrontX = xF;
	cmd.listenerFrontY = yF;
	cmd.listenerFrontZ = zF;
	cmd.listenerTopX = xU;
	cmd.listenerTopY = yU;
	cmd.listenerTopZ = zU;

	CircularData* pOut = SoundEngine::GetG2ABuff();

	pOut->PushBack(cmd);

	return snd_err::OK;
}