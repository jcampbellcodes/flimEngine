#include "Sound.h"
#include "SoundManager.h"
#include "AzulCore.h"
#include "VoiceManager.h"
#include "BufferManager.h"
#include "CallbackCommand.h"
#include "Track.h"
#include "Playlist.h"
#include "SoundManager3D.h"
#include "IndividualSoundEnded.h"


Sound::Sound(WAVEFORMATEXTENSIBLE _wfx, XAUDIO2_BUFFER* _buffer, Playlist* pl) : wfx(_wfx), buffer(*_buffer), track(nullptr), playlist(pl)
{
	lengthInBytes = buffer.AudioBytes;
	startPosition = 0;
	playing = false;

	soundEndedCommand = new IndividualSoundEnded(pl);
	this->emitter = new X3DAUDIO_EMITTER();

	this->emitter->ChannelCount = 1;
	this->emitter->Position = {0,0,0};
	this->emitter->pVolumeCurve = 0;
	this->emitter->ChannelRadius = 0;
	this->emitter->pCone = nullptr;
	this->emitter->OrientFront = {0,0,1};
	this->emitter->OrientTop = {0,1,0};
	this->emitter->CurveDistanceScaler = FLT_MIN;

	this->dspSettings = new X3DAUDIO_DSP_SETTINGS();


}

Sound::~Sound()
{
	//SoundManager::Remove(this);
	if (soundEndedCommand)
	{
		//delete soundEndedCommand;
		soundEndedCommand = nullptr;
	}

	if (emitter)
	{
		delete emitter;
		emitter = nullptr;
	}

	if (dspSettings)
	{
		delete dspSettings;
		dspSettings = nullptr;
	}

	while (this->cmdStack.size())
	{
		cmdStack.pop();
	}

	if (track)
	{
		track = nullptr;
		// return voice to voice manager
		//VoiceManager::ReturnVoice(track, wfx);
		//delete track;
	}
	//DebugMsg::out("sound destroyed\n");
}

snd_err Sound::Play()
{
	if (track)
	{

		//track->voice->Start(startPosition);
		track->voice->FlushSourceBuffers();
		track->voice->SubmitSourceBuffer(&this->buffer);

		//this->SubmitCallback(soundEndedCommand);
		
		track->voice->Start();
		playing = true;
		return snd_err::OK;
	}

	return snd_err::NO_TRACK;
}

snd_err Sound::Stop()
{
	if (track)
	{
		track->voice->Stop();

		playing = false;
		//track->voice->FlushSourceBuffers();
		return snd_err::OK;
	}

	return snd_err::NO_TRACK;
}

snd_err Sound::Pause()
{
	if (track)
	{
		track->voice->Stop();
		playing = false;
		//track->voice->get
		return snd_err::OK;
	}

	return snd_err::NO_TRACK;
}

snd_err Sound::Pan(float pan)
{
	if (track)
	{
		// doesnt work now
		
		pan;

		return snd_err::OK;
	}

	return snd_err::NO_TRACK;
}

snd_err Sound::Pitch(float pitch)
{
	if (track)
	{
		track->voice->SetFrequencyRatio(pitch);
		return snd_err::OK;
	}

	return snd_err::NO_TRACK;
}

snd_err Sound::Volume(float volume)
{
	if (track)
	{
		track->voice->SetVolume(volume);
		return snd_err::OK;
	}

	return snd_err::NO_TRACK;
}

snd_err Sound::Loop(bool toLoop)
{
	if (track)
	{
		track->voice->FlushSourceBuffers();
		if (toLoop)
		{
			buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
		}
		else
		{
			track->voice->ExitLoop();
			buffer.LoopCount = 0;
		}
		return snd_err::OK;
	}

	return snd_err::NO_TRACK;
}

snd_err Sound::SubmitCallback(CallbackCommand * cmd)
{
	snd_err err = snd_err::OK;
	if (track)
	{
		if (cmd)
		{
			track->cbMailbox->SubmitCallback(cmd);
		}
		else
		{
			err = snd_err::NULLPTR;
		}
	}
	else
	{
		this->cmdStack.push(cmd);
		err = snd_err::NO_TRACK;
	}
	return err;
}

snd_err Sound::SendToTrack(int priority)
{
	snd_err status = snd_err::OK;
	if (!track)
	{
		status = VoiceManager::GetVoice(this->track, wfx, priority, this);

		// now that we have a voice and are being prepared to play, we have somewhere to send commands that were added at weird times
		if (status == snd_err::OK)
		{
			track->voice->SubmitSourceBuffer(&buffer);
			while (!this->cmdStack.empty())
			{
				this->SubmitCallback(cmdStack.top());
				this->cmdStack.pop();
			}
		}
		else
		{
			status = snd_err::NO_TRACK;
		}
	}

	return status;
}

snd_err Sound::AddToChannel(Channel * channel)
{
	if (track)
	{
		XAUDIO2_SEND_DESCRIPTOR sendDesc = { 0,channel->GetSubmixVoice() };
		XAUDIO2_VOICE_SENDS sendList = { 1, &sendDesc };
		this->track->voice->SetOutputVoices(&sendList);
	}
	else
	{
		return snd_err::NO_TRACK;
	}

	return snd_err::OK;
}

snd_err Sound::setEmitterPos(float , float , float )
{
	snd_err err = snd_err::OK;
	/*
	if (track)
	{
		this->emitter->Position = { x, y, z };
		SoundManager3D::CalculateEmitterValues(this->emitter, this->dspSettings);
		SoundManager::PanSound(this->track->voice, this->dspSettings);
	}
	else
	{
		err = snd_err::NO_TRACK;
	}
	*/
	return err;
}

snd_err Sound::ClearTrack()
{
	snd_err err = snd_err::OK;
	if (track)
	{
		this->track = nullptr;
	}
	else
	{
		err = snd_err::NO_TRACK;
	}
	return err;
}

bool Sound::IsPlaying()
{
	return playing;
}

unsigned int Sound::LengthInBytes()
{
	return lengthInBytes;
}
