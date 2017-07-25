#include "SoundManager3D.h"
#include "SoundManager.h"
#include "..\Flim\TimeManager.h"
#include "AzulCore.h"
#include "Playlist.h"
#include "Trace\Trace.h"

// Specify sound cone to add directionality to listener for artistic effect:
// Emitters behind the listener are defined here to be more attenuated,
// have a lower LPF cutoff frequency,
// yet have a slightly higher reverb send level.
static const X3DAUDIO_CONE Listener_DirectionalCone = { X3DAUDIO_PI*5.0f / 6.0f, X3DAUDIO_PI*11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };

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



SoundManager3D* SoundManager3D::instance = nullptr;

SoundManager3D::SoundManager3D() : x3DAudio()
{
	SoundManagerInfo info;
	SoundManager::GetInfo(info);

	X3DAUDIO_HANDLE handle;
	X3DAudioInitialize(SPEAKER_STEREO, X3DAUDIO_SPEED_OF_SOUND, handle);

	listener = new X3DAUDIO_LISTENER();
	listener->pCone = nullptr;//new X3DAUDIO_CONE { X3DAUDIO_PI*5.0f / 6.0f, X3DAUDIO_PI*11.0f / 6.0f, 1.0f, 0.75f, 0.0f, 0.25f, 0.708f, 1.0f };



	//this->listener->OrientFront = { -1,0,0 };
	//this->listener->OrientTop = { 0,1,0 };
	//this->listener->pCone->InnerVolume = 1.0f;
	//this->listener->pCone->OuterVolume = 1.0f;
	//this->listener->pCone->OuterAngle = X3DAUDIO_PI / 2;
	//
	// Setup 3D audio structs
	//
	listener->Position.x = 0;
	listener->Position.y = 0;
	listener->Position.z = 0;

	listener->OrientFront.x =
	listener->OrientFront.y =
		listener->OrientTop.x =
		listener->OrientTop.z = 0.f;

	listener->OrientFront.z =
		listener->OrientTop.y = 1.f;



}

SoundManager3D::~SoundManager3D()
{
	// clean up audio stuff
	if (listener)
	{
		delete listener;
		listener = nullptr;
	}
}

snd_err SoundManager3D::privUpdatePosition(float x, float y, float z)
{
	snd_err err = snd_err::OK;

	if (!listener) return snd_err::NULLPTR;
	this->pos = { x,y,z };
	/*

	X3DAUDIO_VECTOR v2 = {x,y,z};

	X3DAUDIO_VECTOR vDelta = { pos.x - v2.x, pos.y - v2.y, pos.z - v2.z };

	float listener_angle = float(atan2(vDelta.x, vDelta.z));

	Vect tmp = { vDelta.x, 0, vDelta.z };
	tmp.norm();
	listener->pCone->InnerAngle = listener_angle;
	listener->pCone->OuterAngle = listener_angle;
	this->listener->OrientFront.x = tmp.X();
	this->listener->OrientFront.y = 0.f;
	this->listener->OrientFront.z = tmp.Z();


	this->pos = { x, y, z };

	this->listener->Position = this->pos;
	*/

	return err;
}




snd_err SoundManager3D::privUpdateOrientation(float xF, float yF, float zF, float xU, float yU, float zU)
{
	snd_err err = snd_err::OK;

	if (!listener) return snd_err::NULLPTR;

	//this->pos = { x, y, z };


	Vect _front = Vect(xF, yF, zF).norm();
	Vect _up = Vect(xU, yU, zU).norm();

	this->listener->OrientFront = { _front.X(), _front.Y(), _front.Z() };
	this->listener->OrientTop = { _up.X(), _up.Y(), _up.Z() };

	// 
	// 
	// 
	xF, yF, zF, xU, yU, zU;
	//this->listener->pCone->InnerAngle = X3DAUDIO_2PI;
	//this->listener->pCone->OuterAngle = 0.0f;


	return err;
}

snd_err SoundManager3D::privCalculate(X3DAUDIO_EMITTER *& emit, X3DAUDIO_DSP_SETTINGS*& dspSettings)
{
	snd_err err = snd_err::OK;

	if (!(listener && emit && dspSettings))
	{
		err = snd_err::NULLPTR;
		return err;
	}

	X3DAudioCalculate(this->x3DAudio, this->listener, emit, X3DAUDIO_CALCULATE_MATRIX, dspSettings);


	return err;
}



snd_err SoundManager3D::privUpdate3DAudio()
{
	float fElapsedTime = FlimTime::FrameTime();
	
	listener->pCone = NULL;
	// Calculate listener orientation in x-z plane
	//if (pos.x != listener->Position.x
	//	|| pos.x != listener->Position.x
	//	|| pos.y != listener->Position.y)
	{

		X3DAUDIO_VECTOR v2 = pos;

		X3DAUDIO_VECTOR vDelta = { listener->Position.x - v2.x, listener->Position.y - v2.y, listener->Position.z - v2.z };

		//float listener_angle = float(atan2(vDelta.x, vDelta.z));

		//Vect tmp = { vDelta.x, 0, vDelta.z };
		//tmp.norm();
		//listener->pCone->InnerAngle = listener_angle;
		//listener->pCone->OuterAngle = listener_angle;
		//this->listener->OrientFront.x = tmp.X();
		//this->listener->OrientFront.y = tmp.Y();
		//this->listener->OrientFront.z = tmp.Z();

		//this->listener->OrientTop

	}
	//listener->pCone = (X3DAUDIO_CONE*)&Listener_DirectionalCone;
	X3DAUDIO_VECTOR v1 = pos;
	X3DAUDIO_VECTOR v2 = listener->Position;

	X3DAUDIO_VECTOR lVelocity = (X3DAUDIO_VECTOR{ (v1.x - v2.x) / fElapsedTime, (v1.y - v2.y) / fElapsedTime, (v1.z - v2.z) / fElapsedTime });
	listener->Position.x = pos.x;
	listener->Position.y = pos.y;
	listener->Position.z = pos.z;

	//listener->pCone->InnerAngle = X3DAUDIO_2PI;
	//listener->pCone->OuterAngle = 0;
	listener->Velocity = lVelocity;

	//DWORD dwCalcFlags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER
	//	| X3DAUDIO_CALCULATE_LPF_DIRECT | X3DAUDIO_CALCULATE_LPF_REVERB
	//	| X3DAUDIO_CALCULATE_REVERB;


	std::list<Playlist*>::iterator iter = registeredSounds.begin();
	while (iter != registeredSounds.end())
	{

		(*iter)->getChannel()->GetEmitter()->InnerRadius = FLT_MAX;
		
		(*iter)->getChannel()->GetEmitter()->InnerRadiusAngle = 1.0f;
		//(*iter)->getChannel()->GetEmitter()->pCone->OuterAngle = 0.0f;

		//(*iter)->getChannel()->GetEmitter()->OrientFront = listener->OrientFront;
		//(*iter)->getChannel()->GetEmitter()->OrientTop = listener->OrientTop;

		if (fElapsedTime > 0)
		{


			v1 = (*iter)->getChannel()->GetPos(); // nominal emitter position; vector in channel obj
			v2 = (*iter)->getChannel()->GetEmitter()->Position; // actual listener position; member of struct
			(*iter)->getChannel()->GetEmitter()->pCone = NULL;
			(*iter)->getChannel()->GetEmitter()->CurveDistanceScaler = 100.0f;

			X3DAUDIO_VECTOR eVelocity = (X3DAUDIO_VECTOR{ (v1.x - v2.x) / fElapsedTime, (v1.y - v2.y) / fElapsedTime, (v1.z - v2.z) / fElapsedTime });
			(*iter)->getChannel()->GetEmitter()->Position = (*iter)->getChannel()->GetPos();

			(*iter)->getChannel()->GetEmitter()->Velocity = eVelocity;
		}




		X3DAudioCalculate(x3DAudio, listener, (*iter)->getChannel()->GetEmitter(), X3DAUDIO_CALCULATE_MATRIX,
			(*iter)->getChannel()->GetDSPSettings());


		// set values in voice
		//(*iter)->Pitch((*iter)->getChannel()->GetDSPSettings()->DopplerFactor);

		IXAudio2SubmixVoice* submixVoice = (*iter)->getChannel()->GetSubmixVoice();
		X3DAUDIO_DSP_SETTINGS* dsp = (*iter)->getChannel()->GetDSPSettings();

		//dsp->pMatrixCoefficients[1] = dsp->pMatrixCoefficients[0];

		SoundManager::PanSound(submixVoice, dsp);

		//Trace::out("left: %f, right: %f\n", dsp->pMatrixCoefficients[0], dsp->pMatrixCoefficients[1]);
		//Trace::out("doppler: %f\n", (*iter)->getChannel()->GetDSPSettings()->DopplerFactor);
		iter++;
	}
	

	return snd_err::OK;
}

snd_err SoundManager3D::privRegister3DSound(Playlist *p)
{
	this->registeredSounds.push_back(p);
	return snd_err::OK;
}

snd_err SoundManager3D::privDeregister3DSound(Playlist * p)
{
	this->registeredSounds.remove(p);
	return snd_err::OK;
}
