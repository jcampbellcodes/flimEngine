#include "Channel.h"
#include "SoundManager.h"
#include "SoundManager3D.h"


// Specify LFE level distance curve such that it rolls off much sooner than
// all non-LFE channels, making use of the subwoofer more dramatic.
static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_LFE_CurvePoints[3] = { 0.0f, 1.0f, 0.25f, 0.0f, 1.0f, 0.0f };
static const X3DAUDIO_DISTANCE_CURVE       Emitter_LFE_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_LFE_CurvePoints[0], 3 };

// Specify reverb send level distance curve such that reverb send increases
// slightly with distance before rolling off to silence.
// With the direct channels being increasingly attenuated with distance,
// this has the effect of increasing the reverb-to-direct sound ratio,
// reinforcing the perception of distance.
static const X3DAUDIO_DISTANCE_CURVE_POINT Emitter_Reverb_CurvePoints[3] = { 0.0f, 0.5f, 0.75f, 1.0f, 1.0f, 0.0f };
static const X3DAUDIO_DISTANCE_CURVE       Emitter_Reverb_Curve = { (X3DAUDIO_DISTANCE_CURVE_POINT*)&Emitter_Reverb_CurvePoints[0], 3 };



XAUDIO2FX_REVERB_I3DL2_PARAMETERS g_PRESET_PARAMS[30] =
{
/*0	*/XAUDIO2FX_I3DL2_PRESET_FOREST,
/*1	*/XAUDIO2FX_I3DL2_PRESET_DEFAULT,
/*2	*/XAUDIO2FX_I3DL2_PRESET_GENERIC,
/*3	*/XAUDIO2FX_I3DL2_PRESET_PADDEDCELL,
/*4	*/XAUDIO2FX_I3DL2_PRESET_ROOM,
/*5	*/XAUDIO2FX_I3DL2_PRESET_BATHROOM,
/*6	*/XAUDIO2FX_I3DL2_PRESET_LIVINGROOM,
/*7	*/XAUDIO2FX_I3DL2_PRESET_STONEROOM,
/*8	*/XAUDIO2FX_I3DL2_PRESET_AUDITORIUM,
/*9	*/XAUDIO2FX_I3DL2_PRESET_CONCERTHALL,
/*10*/	XAUDIO2FX_I3DL2_PRESET_CAVE,
/*11*/	XAUDIO2FX_I3DL2_PRESET_ARENA,
/*12*/	XAUDIO2FX_I3DL2_PRESET_HANGAR,
/*13*/	XAUDIO2FX_I3DL2_PRESET_CARPETEDHALLWAY,
/*14*/	XAUDIO2FX_I3DL2_PRESET_HALLWAY,
/*15*/	XAUDIO2FX_I3DL2_PRESET_STONECORRIDOR,
/*16*/	XAUDIO2FX_I3DL2_PRESET_ALLEY,
/*17*/	XAUDIO2FX_I3DL2_PRESET_CITY,
/*18*/	XAUDIO2FX_I3DL2_PRESET_MOUNTAINS,
/*19*/	XAUDIO2FX_I3DL2_PRESET_QUARRY,
/*20*/	XAUDIO2FX_I3DL2_PRESET_PLAIN,
/*21*/	XAUDIO2FX_I3DL2_PRESET_PARKINGLOT,
/*22*/	XAUDIO2FX_I3DL2_PRESET_SEWERPIPE,
/*23*/	XAUDIO2FX_I3DL2_PRESET_UNDERWATER,
/*24*/	XAUDIO2FX_I3DL2_PRESET_SMALLROOM,
/*25*/	XAUDIO2FX_I3DL2_PRESET_MEDIUMROOM,
/*26*/	XAUDIO2FX_I3DL2_PRESET_LARGEROOM,
/*27*/	XAUDIO2FX_I3DL2_PRESET_MEDIUMHALL,
/*28*/	XAUDIO2FX_I3DL2_PRESET_LARGEHALL,
/*29*/	XAUDIO2FX_I3DL2_PRESET_PLATE,
};



Channel::Channel(IXAudio2SubmixVoice * submix, IXAudio2SubmixVoice * reverb) : voice(submix), params(nullptr), cutoffFrequency(1.0f), reverbParams()
{
	if (reverb)
	{
		reverbReturn = reverb;
	}


	ReverbConvertI3DL2ToNative(&g_PRESET_PARAMS[18], &reverbParams);

	reverbReturn->SetEffectParameters(0, &reverbParams, sizeof(XAUDIO2FX_REVERB_PARAMETERS));
	reverbReturn->SetVolume(0);


	this->emitter = new X3DAUDIO_EMITTER();
	
	this->emitter->pCone = new X3DAUDIO_CONE();
	
	emitter->pCone->InnerAngle = X3DAUDIO_2PI;
	// Setting the inner cone angles to X3DAUDIO_2PI and
	// outer cone other than 0 causes
	// the emitter to act like a point emitter using the
	// INNER cone settings only.
	emitter->pCone->OuterAngle = 1.0f;
	// Setting the outer cone angles to zero causes
	// the emitter to act like a point emitter using the
	// OUTER cone settings only.
	emitter->pCone->InnerVolume = 1.0f;
	emitter->pCone->OuterVolume = 1.0f;
	emitter->pCone->InnerLPF = 0.0f;
	emitter->pCone->OuterLPF = 1.0f;
	emitter->pCone->InnerReverb = 0.0f;
	emitter->pCone->OuterReverb = 1.0f;

	emitter->Position = { 0,0,0 };

	
	emitter->OrientFront.x =
		emitter->OrientFront.y =
		emitter->OrientTop.x =
		emitter->OrientTop.z = 0.f;

	emitter->OrientFront.z =
		emitter->OrientTop.y = 1.f;
		
	emitter->ChannelCount = 1;
	emitter->ChannelRadius = 100.0f;
	emitter->pChannelAzimuths = new float[1];

	// Use of Inner radius allows for smoother transitions as
	// a sound travels directly through, above, or below the listener.
	// It also may be used to give elevation cues.
	emitter->InnerRadius = 20000.0f;
	emitter->InnerRadiusAngle = X3DAUDIO_PI / 4.0f;

	emitter->pVolumeCurve = nullptr;//(X3DAUDIO_DISTANCE_CURVE*)&X3DAudioDefault_LinearCurve;
	emitter->pLFECurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_LFE_Curve;
	emitter->pLPFDirectCurve = nullptr; // use default curve
	emitter->pLPFReverbCurve = nullptr; // use default curve
	emitter->pReverbCurve = (X3DAUDIO_DISTANCE_CURVE*)&Emitter_Reverb_Curve;
	emitter->CurveDistanceScaler = 14.0f;
	emitter->DopplerScaler = 1.0f;

	
	emitter->pCone = nullptr;
	

	
	this->emitter->ChannelCount = 1;
	this->emitter->Position = { 0,0,0 };
	this->emitter->pVolumeCurve = NULL;
	this->emitter->ChannelRadius = 0;
	this->emitter->InnerRadius = 100000.0f;
	this->emitter->InnerRadiusAngle = 0.0f;
	
	//emitter->pCone->InnerVolume = 2.0f;
	//emitter->pCone->InnerAngle = 0.0f;
	//emitter->pCone->OuterAngle = X3DAUDIO_PI / 2;
	//emitter->pCone->OuterVolume = 0.5f;
	//this->emitter->OrientFront = { 0,0,0 };
	//this->emitter->OrientTop = { 0,0,0 };
	this->emitter->CurveDistanceScaler = 200.0f;
	

	


	SoundManagerInfo info;
	SoundManager::GetInfo(info);
	this->dspSettings = new X3DAUDIO_DSP_SETTINGS();
	XAUDIO2_VOICE_DETAILS details;
	voice->GetVoiceDetails(&details);
	FLOAT32 * matrix = new FLOAT32[6];
	matrix[0] = 0.0f;
	matrix[1] = 1.0f;
	dspSettings->SrcChannelCount = details.InputChannels;
	dspSettings->DstChannelCount = info.voiceDetails.InputChannels;
	dspSettings->pMatrixCoefficients = matrix;
	dspSettings->pDelayTimes = nullptr;


	params = new XAUDIO2_FILTER_PARAMETERS();

	params->Type = XAUDIO2_FILTER_TYPE::LowPassFilter;
	params->Frequency = 1.0f;
	params->OneOverQ = 1.0f;

	assert(params);
	//this->voice->SetFilterParameters(params);

};


snd_err Channel::SetReverbLevel(float level)
{
	reverbReturn->SetVolume(1.0f);
	reverbParams.ReverbGain = level;

	this->reverbReturn->SetEffectParameters(0, &reverbParams, sizeof(XAUDIO2FX_REVERB_PARAMETERS));

	return snd_err::OK;
}

snd_err Channel::SetReverbTime(float time)
{
	reverbParams.DecayTime = time;

	this->reverbReturn->SetEffectParameters(0, &reverbParams, sizeof(XAUDIO2FX_REVERB_PARAMETERS));

	return snd_err::OK;
}

snd_err Channel::SetReverbPreDelay(float time)
{
	reverbParams.ReverbDelay = static_cast<BYTE>(time);

	this->reverbReturn->SetEffectParameters(0, &reverbParams, sizeof(XAUDIO2FX_REVERB_PARAMETERS));
	return snd_err::OK;
}

snd_err Channel::SetReverbSize(float size)
{
	reverbParams.RoomSize = size;

	this->reverbReturn->SetEffectParameters(0, &reverbParams, sizeof(XAUDIO2FX_REVERB_PARAMETERS));
	return snd_err::OK;
}

snd_err Channel::SetReverbDensity(float density)
{
	reverbParams.Density = density;

	this->reverbReturn->SetEffectParameters(0, &reverbParams, sizeof(XAUDIO2FX_REVERB_PARAMETERS));
	return snd_err::OK;
}

snd_err Channel::SetReverbPreset(flimReverb reverb)
{

	switch (reverb)
	{
	case flimReverb::CORRIDOR:
	{
		ReverbConvertI3DL2ToNative(&g_PRESET_PARAMS[15], &reverbParams);
		break;
	}
	case flimReverb::LARGE_ROOM:
	{
		ReverbConvertI3DL2ToNative(&g_PRESET_PARAMS[26], &reverbParams);
		break;
	}
	case flimReverb::MOUNTAIN:
	{
		ReverbConvertI3DL2ToNative(&g_PRESET_PARAMS[18], &reverbParams);
		break;
	}
	case flimReverb::PLATE:
	{
		ReverbConvertI3DL2ToNative(&g_PRESET_PARAMS[29], &reverbParams);
		break;
	}
	case flimReverb::SMALL_ROOM:
	{
		ReverbConvertI3DL2ToNative(&g_PRESET_PARAMS[24], &reverbParams);
		break;
	}

	default:
		break;
	}



	reverbReturn->SetEffectParameters(0, &reverbParams, sizeof(XAUDIO2FX_REVERB_PARAMETERS));

	return snd_err::OK;
}







IXAudio2SubmixVoice * Channel::GetSubmixVoice() const
{
	return voice;
}

Channel::~Channel()
{
	voice->DestroyVoice();
	reverbReturn->DestroyVoice();
}

snd_err Channel::Pan(float pan)
{
	// generate matrix
	float mat[8] = { 0 };
	// calculate peker values based on pan
	float left = 0.5f - pan / 2.0f;
	float right = 0.5f + pan / 2.0f;
	mat[0] = left;
	mat[1] = right;

	// send to voice
	SoundManagerInfo info;
	SoundManager::GetInfo(info);
	XAUDIO2_VOICE_DETAILS masteringVoiceDetails = info.voiceDetails;
	XAUDIO2_VOICE_DETAILS sourceVoiceDetails;
	X3DAUDIO_DSP_SETTINGS dsp;
	dsp.pMatrixCoefficients = mat;
	voice->GetVoiceDetails(&sourceVoiceDetails);

	//SoundManager::PanSound(voice, &dsp);

	//voice->SetOutputMatrix(SoundManager::pa, sourceVoiceDetails.InputChannels, 1, mat);

	return snd_err::OK;
}

snd_err Channel::setEmitterPos(float x, float y, float z)
{
	snd_err err = snd_err::OK;

	this->vPosition = {x,y,z};

	/*
	X3DAUDIO_VECTOR v2 = { x,y,z };

	X3DAUDIO_VECTOR vDelta = { this->emitter->Position.x - v2.x, 	this->emitter->Position.y - v2.y, 	this->emitter->Position.z - v2.z };

	float listener_angle = float(atan2(vDelta.x, vDelta.z));

	Vect tmp = { vDelta.x, 0, vDelta.z };
	tmp.norm();
	this->emitter->pCone->InnerAngle = listener_angle;
	this->emitter->pCone->OuterAngle = listener_angle;
	this->emitter->OrientFront.x = tmp.X();
	this->emitter->OrientFront.y = 0.f;
	this->emitter->OrientFront.z = tmp.Z();
	this->emitter->Position = { x, y, z };
	Trace::out("left: %f, right: %f\n", dspSettings->pMatrixCoefficients[0], dspSettings->pMatrixCoefficients[1]);
	SoundManager3D::CalculateEmitterValues(this->emitter, this->dspSettings);
	SoundManager::PanSound(this->voice, this->dspSettings);
	*/
	return err;
}

snd_err Channel::setEmitterOrientation(float , float , float , float , float , float )
{
	snd_err err = snd_err::OK;

	//this->emitter->OrientFront = { xF, yF, zF };
	//this->emitter->OrientTop = { xU, yU, zU };
	//Trace::out("left: %f, right: %f\n", dspSettings->pMatrixCoefficients[0], dspSettings->pMatrixCoefficients[1]);
	//SoundManager3D::CalculateEmitterValues(this->emitter, this->dspSettings);
	//SoundManager::PanSound(this->voice, this->dspSettings);

	return err;
}

snd_err Channel::Volume(float volume)
{
	if (volume < FLT_MIN)
	{
		volume = 0.0f;
	}
	voice->SetVolume(volume);
	return snd_err::OK;
}

snd_err Channel::ActivateFilter(FilterType type)
{
	this->params->Frequency = cutoffFrequency;
	this->params->OneOverQ = 1.0f;

	XAUDIO2_FILTER_TYPE typeXAudio;

	if (type == FilterType::HiPass)
	{
		typeXAudio = XAUDIO2_FILTER_TYPE::HighPassFilter;
	}
	else if (type == FilterType::LoPass)
	{
		typeXAudio = XAUDIO2_FILTER_TYPE::LowPassFilter;
	}
	else
	{
		return snd_err::ERR;
	}

	this->params->Type = typeXAudio;
	this->voice->SetFilterParameters(params);
	return snd_err();
}

snd_err Channel::DeactivateFilter(FilterType )
{
	this->params->Frequency = 1.0f;
	this->params->Type = XAUDIO2_FILTER_TYPE::LowPassFilter;
	return snd_err();
}

snd_err Channel::SetCutoff(float cutoff)
{
	SoundManagerInfo info;
	SoundManager::GetInfo(info);

	this->cutoffFrequency = XAudio2CutoffFrequencyToRadians(cutoff, info.voiceDetails.InputSampleRate);
	this->params->Frequency = cutoffFrequency;
	this->params->Type = XAUDIO2_FILTER_TYPE::LowPassFilter;
	this->params->OneOverQ = 1.0f;
	this->voice->SetFilterParameters(params);
	return snd_err::OK;
}

snd_err Channel::GetCutoff(float & )
{
	return snd_err::OK;
}
