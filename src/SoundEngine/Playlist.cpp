#include "Playlist.h"
#include "SoundManager.h"
#include "Sound.h"
#include "CallbackSoundEndedCommand.h"
#include "HashThis.h"
#include "CallbackCommand.h"
#include "PlayCmd.h"
#include "PanCmd.h"
#include "LoopCommand.h"
#include "PitchCommand.h"
#include "VolumeCommand.h"
#include "SoundManager.h"
#include "AudioMain.h"
#include "TransitionOnEnd.h"
#include "AssignCallbackCommand.h"
#include "InternalSoundEnded.h"
#include "SoundManager3D.h"
#include "AudioCommandTypes\CallbackSoundEndedType.h"
#include "SoundEngine.h"

Playlist::Playlist(SoundCallID _id, unsigned int instance, bool _3D) : id(_id), soundsLoaded(false), instanceNumber(instance), numSoundsPlaying(0), is3D(_3D)
{
	SoundManager::CreateChannel(channel);
	isPlaying = false;
	loop = false;
	this->internalSoundEnded = new InternalSoundEnded(this);

	if(is3D)
	{
		SoundManager3D::Register3DSound(this);
	}


	assert(channel);
}

CmdWithTime::~CmdWithTime()
{
	if (cmd)
	{
		//delete cmd;
		cmd = nullptr;
	}
}

Playlist::~Playlist()
{
	// CLEAN OUT PLAYLIST LISTS + MAP
	if(is3D) SoundManager3D::Deregister3DSound(this);

	if (internalSoundEnded)
	{
		//delete internalSoundEnded;
	}

	// clean list of cmds
	std::list<CmdWithTime*>::iterator cmdIter = commands.begin();
	while (cmdIter != commands.end())
	{
		delete (*cmdIter);
		(*cmdIter) = nullptr;
		cmdIter++;
	}
	commands.clear();

	/*
	// clean map of sounds
	std::map<unsigned int, Sound*>::iterator sndIter = sounds.begin();
	while (sndIter != sounds.end())
	{
		delete (*sndIter).second;
		sndIter++;
	}
	*/
	if (channel)
	{
		delete channel;
	}

}

snd_err Playlist::PrepareToPlay()
{
	snd_err err = snd_err::OK;
	// grab voices for all the sounds
	// put sounds in a channel

	numSoundsPlaying = sounds.size();

	std::map<unsigned int, Sound*>::iterator iter = sounds.begin();
	while (iter != sounds.end())
	{
		// gets voice
		err = (*iter).second->SendToTrack(0);
		if (err == snd_err::NO_TRACK) // loses priority!
		{
			break;
		}
		// submix voice for entire playlist
		err = (*iter).second->AddToChannel(channel);
		iter++;
	}
	// all geared up!

	soundsLoaded = true;

	return err;
}

snd_err Playlist::AddSound(const char * sndName)
{
	snd_err err = snd_err::OK;
	if (sndName)
	{
		Sound* snd = nullptr;
		unsigned int sndHash = HashThis(sndName);

		err = SoundManager::GetSound(snd, sndHash, this);

		if (err == snd_err::OK)
		{
			this->sounds.insert(std::pair<unsigned int, Sound*>(sndHash, snd));
		}
	}
	else
	{
		err = snd_err::ERR;
	}
	return err;
}

snd_err Playlist::AddSound(unsigned int sndName)
{
	snd_err err = snd_err::OK;
	if (sndName)
	{
		Sound* snd = nullptr;
		unsigned int sndHash = sndName;

		err = SoundManager::GetSound(snd, sndHash, this);

		if (err == snd_err::OK)
		{
			this->sounds.insert(std::pair<unsigned int, Sound*>(sndHash, snd));
		}
	}
	else
	{
		err = snd_err::ERR;
	}
	return err;
}


snd_err Playlist::AddCommand(AudioCommand * cmd, int time, unsigned int _id)
{
	snd_err err = snd_err::OK;
	cmd->AttachSound(this->sounds.at(_id));
	cmd->AssignPlaylistID(instanceNumber);

	CmdWithTime* command = new CmdWithTime();
	command->cmd = cmd;
	command->cmd->AssignPlaylistID(instanceNumber);
	command->time = time;

	if (cmd)
	{
		this->commands.push_back(command);
	}
	else
	{
		err = snd_err::ERR;
	}
	return err;
}

snd_err Playlist::AddCommand(AudioCommand * cmd, int time)
{
	snd_err err = snd_err::OK;
	cmd->AssignPlaylistID(instanceNumber);

	CmdWithTime* command = new CmdWithTime();
	command->cmd = cmd;
	command->cmd->AssignPlaylistID(instanceNumber);
	command->time = time;

	if (cmd)
	{
		this->commands.push_back(command);
	}
	else
	{
		err = snd_err::ERR;
	}
	return err;
}

// special for callbacks
snd_err Playlist::AddCommand(CallbackCommand * cmd, int time, unsigned int id1, unsigned int id2 = 0)
{
	snd_err err = snd_err::OK;
	cmd->AttachSound(this->sounds.at(id1));
	cmd->AssignPlaylistID(instanceNumber);
	if (id2)
	{
		cmd->AttachSecondarySound(this->sounds.at(id2));
	}
	CmdWithTime* command = new CmdWithTime();
	command->cmd = new AssignCallbackCommand(cmd);
	command->cmd->AttachSound(this->sounds.at(id1));
	command->cmd->AssignPlaylistID(instanceNumber);
	command->time = time;

	if (cmd)
	{
		this->commands.push_back(command);
	}
	else
	{
		err = snd_err::ERR;
	}

	return err;
}

snd_err Playlist::SendCallbackSoundEnded()
{
	snd_err err = snd_err::OK;

	//CallbackSoundEndedCommand* cmd = new CallbackSoundEndedCommand(this->id, this->instanceNumber);
	//cmd;
	ThreadCommand cmd;
	cmd.handle = this->instanceNumber;
	cmd.id = this->id;
	cmd.type = new CallbackSoundEndedType();
	SoundEngine::SendData(cmd);

	return err;
}

snd_err Playlist::setEmitterPos(float x, float y, float z)
{
	// loops through all active sounds and updates position

	/*
	std::map<unsigned int, Sound*>::iterator iterSnd = sounds.begin();
	while (iterSnd != sounds.end())
	{
		(*iterSnd).second->setEmitterPos(x, y, z);
		iterSnd++;
	}
	*/

	this->channel->setEmitterPos(x, y, z);

	return snd_err::OK;
}

snd_err Playlist::setEmitterOrientation(float xF, float yF, float zF, float xU, float yU, float zU)
{
	this->channel->setEmitterOrientation(xF, yF, zF, xU, yU, zU);
	return snd_err::OK;
}

snd_err Playlist::SoundEnded()
{
	if (numSoundsPlaying > 0)
	{
		numSoundsPlaying--;
	}
	else
	{
		return snd_err::ERR;
	}
	if(numSoundsPlaying <= 0)
	{

		if (loop) // here, decide to loop
		{
			this->Play(true);
		}
		else
		{
			internalSoundEnded->execute();
		}



	}
	return snd_err::OK;
}

snd_err Playlist::Play(bool toLoop) // start the commands
{
	snd_err err = snd_err::OK;

	this->numSoundsPlaying = sounds.size();

	this->loop = toLoop;

	if (!soundsLoaded)
	{
		this->PrepareToPlay();
	}

	std::list<CmdWithTime*>::iterator iter = commands.begin();
	while (iter != commands.end())
	{
		SoundManager::InsertTimelineCommand((*iter)->cmd, (*iter)->time);
		iter++;
	}

	startTime.tic();
	isPlaying = true;

	return err;
}

snd_err Playlist::Stop() // stop commands ------- may have to do some thinking here...
{
	snd_err err = snd_err::OK;
	if (isPlaying)
	{


		std::map<unsigned int, Sound*>::iterator iterSnd = sounds.begin();
		while (iterSnd != sounds.end())
		{
			(*iterSnd).second->Stop();
			iterSnd++;
		}



		// clean list of cmds
		std::list<CmdWithTime*>::iterator cmdIter = commands.begin();
		while (cmdIter != commands.end())
		{
			delete (*cmdIter);
			(*cmdIter) = nullptr;
			cmdIter++;
		}
		commands.clear();

		// clean map of sounds
		std::map<unsigned int, Sound*>::iterator sndIter = sounds.begin();
		while (sndIter != sounds.end())
		{
			SoundManager::UnloadSound((*sndIter).second);
			sndIter++;
		}

		if (channel)
		{
			//delete channel;
		}
		SoundManager::CancelPlaylist(this->instanceNumber);
		isPlaying = false;

	}
	else
	{
		err = snd_err::NOT_IN_USE;
	}
	return err;
}

snd_err Playlist::Pause() // take commands off queue and accumulates offset in case you un-pause
{
	// ooooo mama
	snd_err err = snd_err::OK;

	SoundManager::CancelPlaylist(this->instanceNumber);

	const Time elapsedTime = startTime.toc();
	int stopTime = Time::quotient(elapsedTime, Time(TIME_ONE_MILLISECOND));

	std::list<CmdWithTime*>::iterator iterCmd = commands.begin();
	std::list<CmdWithTime*>::iterator iterCmdDelete = commands.begin();
	int adjustedTime = 0;
	while (iterCmd != commands.end())
	{
		adjustedTime = (*iterCmd)->time - stopTime;
		if (adjustedTime < 0) // command already happened
		{
			iterCmdDelete = iterCmd;
			iterCmd++;
			commands.remove(*iterCmdDelete);
		}
		else // keep the command to use later but adjust time
		{
			
			(*iterCmd)->time = adjustedTime;
			iterCmd++;
		}

	}

	std::map<unsigned int, Sound*>::iterator iterSnd = sounds.begin();
	while (iterSnd != sounds.end())
	{

		if ((*iterSnd).second->IsPlaying())
		{
			(*iterSnd).second->Pause(); // does this work right?
			this->AddCommand(new PlayCommand((*iterSnd).second), 0);
		}
		iterSnd++;
	}

	return err;
}

snd_err Playlist::Pan(float pan) // pan the submix voice
{
	snd_err err = snd_err::OK;
	if (channel)
	{
		this->channel->Pan(pan);
	}
	else
	{
		err = snd_err::NULLPTR;
	}

	return err;
}

snd_err Playlist::Loop(bool toLoop)
{
	loop = toLoop;
	return snd_err::OK;
}

snd_err Playlist::Pitch(float pitch) // loop through each sound and change pitch
{
	snd_err err = snd_err::OK;
	std::map<unsigned int, Sound*>::iterator iterSnd = sounds.begin();
	while (iterSnd != sounds.end())
	{
		(*iterSnd).second->Pitch(pitch); // does this work right?
		iterSnd++;
	}
	return err;
}

snd_err Playlist::Volume(float volume) // volume for the submix voice
{
	snd_err err = snd_err::OK;
	if (channel)
	{
		this->channel->Volume(volume);
	}
	else
	{
		err = snd_err::NULLPTR;
	}
	return err;
}

snd_err Playlist::ActivateFilter(FilterType type)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->ActivateFilter(type);

	return snd_err::OK;
}

snd_err Playlist::DeactivateFilter(FilterType type)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->DeactivateFilter(type);

	return snd_err::OK;
}

snd_err Playlist::SetCutoff(float cutoff)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->SetCutoff(cutoff);

	return snd_err::OK;
}

snd_err Playlist::GetCutoff(float & cutoff)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	return channel->GetCutoff(cutoff);
}











snd_err Playlist::SetReverbLevel(float level)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->SetReverbLevel(level);

	return snd_err::OK;
}

snd_err Playlist::SetReverbTime(float time)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->SetReverbTime(time);

	return snd_err::OK;
}

snd_err Playlist::SetReverbPreDelay(float time)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->SetReverbPreDelay(time);

	return snd_err::OK;
}

snd_err Playlist::SetReverbSize(float size)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->SetReverbSize(size);

	return snd_err::OK;
}

snd_err Playlist::SetReverbDensity(float density)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->SetReverbDensity(density);

	return snd_err::OK;
}

snd_err Playlist::SetReverbPreset(flimReverb reverb)
{
	if (!channel)
	{
		return snd_err::NULLPTR;
	}

	channel->SetReverbPreset(reverb);

	return snd_err::OK;
}












bool Playlist::IsPlaying()
{
	return isPlaying;
}

unsigned int Playlist::GetInstanceNumber()
{
	return instanceNumber;
}
