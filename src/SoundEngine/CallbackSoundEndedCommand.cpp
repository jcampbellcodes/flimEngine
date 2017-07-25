#include "CallbackSoundEndedCommand.h"
#include "SoundCallRegistry.h"
#include "SoundEngine.h"

CallbackSoundEndedCommand::CallbackSoundEndedCommand() : id(), handle()
{}

CallbackSoundEndedCommand::CallbackSoundEndedCommand(SoundCallID _id, unsigned int _handle) : id(_id), handle(_handle)
{}

snd_err CallbackSoundEndedCommand::SetContext(SoundCallID _id, unsigned int _handle)
{
	snd_err err = snd_err::OK;

	this->id = _id;
	this->handle = _handle;

	return err;
}

void CallbackSoundEndedCommand::execute()
{
	// search sound engine for sound with the current handle, call its sound ended callback
	// SoundEngine::SoundEndedCallback(handle, id); --> sound engine has a list of lists. Outer list is of tuples that have the id as a key, then an inner list of the instances of that soundcall type
	SoundCall* snd = nullptr;
	SoundEngine::FindSoundCall(snd, handle);
	assert(snd);
	snd->SoundEnded();
}
