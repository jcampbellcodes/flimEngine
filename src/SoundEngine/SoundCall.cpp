#include <assert.h>

#include "CircularData.h"
#include "SoundEngine.h"
#include "SoundCall.h"
#include "HashThis.h"
#include "StartPlaylistCommand.h"
#include "PriorityManager.h"
#include "SoundCallPrintDurationCommand.h"
#include "MarkForStopCommand.h"

#include "AudioCommandTypes\CreatePlaylistType.h"
#include "PlayType.h"
#include "AudioCommandTypes\PanType.h"
#include "AudioCommandTypes\PauseType.h"
#include "AudioCommandTypes\PitchType.h"
#include "AudioCommandTypes\StopType.h"
#include "AudioCommandTypes\LoopType.h"
#include "AudioCommandTypes\VolumeType.h"
#include "AudioCommandTypes\SetReverbDensityType.h"
#include "AudioCommandTypes\SetReverbLevelType.h"
#include "AudioCommandTypes\SetReverbTimeType.h"
#include "AudioCommandTypes\SetReverbPredelay.h"
#include "AudioCommandTypes\SetReverbSizeType.h"
#include "AudioCommandTypes\SetReverbPresetType.h"
#include "AudioCommandTypes\SetEmitterOrientationType.h"
#include "AudioCommandTypes\SetEmitterPositionType.h"

/*
SoundCall::SoundCall(const char* SoundCall)
: handle()
{
	this->id = HashThis(SoundCall);
}
*/

SoundCall::SoundCall(SoundCallID _id, bool _3D) : id(_id), priority(0), is3D(_3D)
{
	priorityIndex = 0;
	this->soundEndedBroker = new SoundExecutioner();
	this->loop = false;
	this->isPlaying = false;
	this->volume = 1.0f;
	this->pan = 0.0f;
	this->pitch = 1.0f;
	this->currentTime = 0;


	// Send a play command to the Audio thread
	CircularData *pOut = SoundEngine::GetG2ABuff();
	assert(pOut);

	//StartPlaylistCommand* cmd = new StartPlaylistCommand();
	//cmd->SetContext(this->id, this->handle.GetID());
	ThreadCommand cmd;
	cmd.handle = this->handle.GetID();
	cmd.id = this->id;
	cmd.type = new CreatePlaylistType();
	cmd.is3D = is3D;
	pOut->PushBack(cmd);


}

SoundCall::SoundCall(SoundCallID _id, int _priority) : id(_id), priority(_priority)
{
	priorityIndex = 0;
	this->soundEndedBroker = new SoundExecutioner();

	this->isPlaying = false;
	this->volume = 1.0f;
	this->pan = 0.0f;
	this->pitch = 1.0f;
	this->currentTime = 0;
	

	// Send a play command to the Audio thread
	CircularData *pOut = SoundEngine::GetG2ABuff();
	assert(pOut);

	//StartPlaylistCommand* cmd = new StartPlaylistCommand();
	//cmd->SetContext(this->id, this->handle.GetID());
	ThreadCommand cmd;
	cmd.handle = this->handle.GetID();
	cmd.id = this->id;
	cmd.type = new CreatePlaylistType();
	pOut->PushBack(cmd);


}

SoundCall::SoundCall(const SoundCall &tmp)
: id(tmp.id),
  handle()
{
}

const SoundCall &SoundCall::operator=(const SoundCall &tmp)
{
	this->id = tmp.id;

	return *this;
}

SoundCall::~SoundCall()
{  
	if (soundEndedBroker)
	{
		delete soundEndedBroker;
		soundEndedBroker = nullptr;
	}
	HandleManager::DeregisterHandle(handle.GetID(), this->handle.GetIndex());
}


snd_err SoundCall::Play(bool toLoop, int t, int _priority)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// priority manager adds to a queue
		this->priority = _priority;
		this->loop = toLoop;
		err = PriorityManager::AddSound(this, priorityIndex, t);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Pan(float p, int triggerTime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->pan = p;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.from = p;
		cmd.to = p;
		cmd.time = 1;
		cmd.triggerTime = triggerTime;
		cmd.type = new PanType();
		pOut->PushBack(cmd);

	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Pan(float from, float to, float _time, int triggerTime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->pan = to;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.from = from;
		cmd.to = to;
		cmd.time = _time;
		cmd.triggerTime = triggerTime;
		cmd.type = new PanType();
		pOut->PushBack(cmd);


	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Loop(bool toLoop, int triggerTime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		//this->loop = toLoop;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.loop = toLoop;
		cmd.triggerTime = triggerTime;
		cmd.type = new LoopType();
		pOut->PushBack(cmd);

	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Pitch(float p, int triggerTime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->pitch = p;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.from = p;
		cmd.to = p;
		cmd.time = 1;
		cmd.triggerTime = triggerTime;
		cmd.type = new PitchType();
		pOut->PushBack(cmd);

	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Pitch(float from, float to, float _time, int triggerTime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->pitch = to;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.from = from;
		cmd.to = to;
		cmd.time = _time;
		cmd.triggerTime = triggerTime;
		cmd.type = new PitchType();
		pOut->PushBack(cmd);

	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Volume(float v, int triggerTime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->volume = v;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.from = v;
		cmd.to = v;
		cmd.time = 1;
		cmd.triggerTime = triggerTime;
		cmd.type = new VolumeType();
		pOut->PushBack(cmd);

	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Volume(float from, float to, float _time, int triggerTime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->volume = to;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.from = from;
		cmd.to = to;
		cmd.time = _time;
		cmd.triggerTime = triggerTime;
		cmd.type = new VolumeType();
		pOut->PushBack(cmd);

	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Stop(int triggerTime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		err = PriorityManager::AddCommand(new MarkForStopCommand(this), triggerTime);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::Pause(int triggerTime)
{

	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->isPlaying = false;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.triggerTime = triggerTime;
		cmd.type = new PauseType();
		pOut->PushBack(cmd);

	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::PrintDuration(int _time, const char* name)
{
	SoundCallPrintDuration* printCmd = new SoundCallPrintDuration(this, name);
	PriorityManager::AddCommand(printCmd, _time);
	return snd_err::OK;
}

snd_err SoundCall::IsPlaying(bool& out)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		out = isPlaying;
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::GetTimeSinceStarted(int& out)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		if (isPlaying)
		{
			const Time elapsedTime = time.toc();
			currentTime = Time::quotient(elapsedTime, Time(TIME_ONE_MILLISECOND));
		}
		out = currentTime;
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::GetVolume(float& out)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		out = volume;
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::GetPitch(float& out)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		out = pitch;
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::GetPan(float& out)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		out = pan;
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::GetPriority(int& out)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		out = priority;
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}


snd_err SoundCall::GetPriorityIndex(int& out)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		out = priorityIndex;
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::GetLoop(bool &out)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		out = loop;
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::SubmitSoundEndedCallback(CallbackCommand * cmd)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->soundEndedBroker->addCommand(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::setPosition(const Vect & vect)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// send thread command
		ThreadCommand cmd;
		cmd.type = new SetEmitterPositionType();
		cmd.emitterPosX = vect.X();
		cmd.emitterPosY = vect.Y();
		cmd.emitterPosZ = vect.Z();
		cmd.handle = this->GetHandleNo();
		CircularData* pOut = SoundEngine::GetG2ABuff();

		pOut->PushBack(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}



snd_err SoundCall::setOrientation(const Vect& vect, float xU = 0.0f, float yU = 1.0f, float zU = 0.0f)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// send thread command
		ThreadCommand cmd;
		cmd.type = new SetEmitterOrientationType();
		cmd.emitterFrontX = vect.X();
		cmd.emitterFrontY = vect.Y();
		cmd.emitterFrontZ = vect.Z();
		cmd.emitterTopX = xU;
		cmd.emitterTopY = yU;
		cmd.emitterTopZ = zU;
		
		cmd.handle = this->GetHandleNo();
		CircularData* pOut = SoundEngine::GetG2ABuff();

		pOut->PushBack(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::SetReverbLevel(float level)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// send thread command
		ThreadCommand cmd;
		cmd.type = new SetReverbLevelType();
		cmd.reverbLevel = level;

		cmd.handle = this->GetHandleNo();
		CircularData* pOut = SoundEngine::GetG2ABuff();

		pOut->PushBack(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::SetReverbTime(float rtime)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// send thread command
		ThreadCommand cmd;
		cmd.type = new SetReverbTimeType();
		cmd.reverbTime = rtime;

		cmd.handle = this->GetHandleNo();
		CircularData* pOut = SoundEngine::GetG2ABuff();

		pOut->PushBack(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::SetReverbPreDelay(float dly)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// send thread command
		ThreadCommand cmd;
		cmd.type = new SetReverbPredelayType();
		cmd.reverbPredelay = dly;

		cmd.handle = this->GetHandleNo();
		CircularData* pOut = SoundEngine::GetG2ABuff();

		pOut->PushBack(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::SetReverbSize(float size)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// send thread command
		ThreadCommand cmd;
		cmd.type = new SetReverbSizeType();
		cmd.reverbSize = size;

		cmd.handle = this->GetHandleNo();
		CircularData* pOut = SoundEngine::GetG2ABuff();

		pOut->PushBack(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::SetReverbDensity(float density)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// send thread command
		ThreadCommand cmd;
		cmd.type = new SetReverbDensityType();
		cmd.reverbDensity = density;

		cmd.handle = this->GetHandleNo();
		CircularData* pOut = SoundEngine::GetG2ABuff();

		pOut->PushBack(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::SetReverbPreset(flimReverb reverb)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		// send thread command
		ThreadCommand cmd;
		cmd.type = new SetReverbPresetType();
		cmd.reverbPreset = reverb;

		cmd.handle = this->GetHandleNo();
		CircularData* pOut = SoundEngine::GetG2ABuff();

		pOut->PushBack(cmd);
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}


snd_err SoundCall::SuccessfullyPlay(int index)
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->priorityIndex = index;
		time.tic();
		this->isPlaying = true;
		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		

		ThreadCommand cmdPan;
		cmdPan.handle = this->handle.GetID();
		cmdPan.id = this->id;
		cmdPan.triggerTime = 0;
		cmdPan.type = new PanType();
		cmdPan.from = this->pan;
		cmdPan.to = this->pan;
		cmdPan.time = 0;
		cmdPan.triggerTime;
		pOut->PushBack(cmdPan);


		ThreadCommand cmdvolume;
		cmdvolume.handle = this->handle.GetID();
		cmdvolume.id = this->id;
		cmdvolume.triggerTime = 0;
		cmdvolume.type = new VolumeType();
		cmdvolume.from = this->volume;
		cmdvolume.to = this->volume;
		cmdvolume.time = 0;
		cmdvolume.triggerTime;
		pOut->PushBack(cmdvolume);


		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.triggerTime = 1;
		cmd.loop = loop;
		cmd.type = new PlayType();
		pOut->PushBack(cmd);

	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

snd_err SoundCall::SuccessfullyStop()
{
	snd_err err = snd_err::OK;
	if (HandleManager::CheckID(handle) == snd_err::OK)
	{
		this->isPlaying = false;
		//PriorityManager::RemoveSound(this->priorityIndex);

		// Send a play command to the Audio thread
		CircularData *pOut = SoundEngine::GetG2ABuff();
		assert(pOut);

		//StartPlaylistCommand* cmd = new StartPlaylistCommand();
		//cmd->SetContext(this->id, this->handle.GetID());
		ThreadCommand cmd;
		cmd.handle = this->handle.GetID();
		cmd.id = this->id;
		cmd.triggerTime = 0;
		cmd.type = new StopType();
		pOut->PushBack(cmd);
		this->SoundEnded();
	}
	else
	{
		return snd_err::ERR;
	}
	return err;
}

unsigned int SoundCall::GetHandleNo()
{
	return handle.GetID();
}

// internal callback
snd_err SoundCall::SoundEnded()
{
	snd_err err = snd_err::OK;

	this->soundEndedBroker->ProcessInstantCommands();

	const Time elapsedTime = time.toc();
	currentTime = Time::quotient(elapsedTime, Time(TIME_ONE_MILLISECOND));

	PriorityManager::RemoveSound(this->priorityIndex);


	return err;
}
