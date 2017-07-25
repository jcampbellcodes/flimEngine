#include "flimSound.h"
#include "FlimListener.h"
#include "..\Flim\MathTools.h"



flimSound::flimSound(SoundCallID _id, bool is3DSound, bool occ) : sndID(_id), is3D(is3DSound), snd(nullptr), position(0,0,0), occlusionEnabled(occ)
{
	SoundEngine::CreateSoundCall(this->snd, sndID, is3DSound);
	this->filter.setSound(snd);

	if (occlusionEnabled)
	{
		this->occlusionSphere = new Model(Model::PreMadedeModels::UnitSphere);
		SetColliderModel(this->occlusionSphere, CollisionVolumeType::OCCLUSION_LINE);

		// register for collisions and update
		SubmitUpdateRegistration();
		SubmitCollisionRegistration<flimSound>(this);

	}

}

flimSound::~flimSound()
{
	//SoundEngine::ReturnSoundCall(this->snd);
	if (occlusionEnabled)
	{
		// register for collisions and update
		SubmitUpdateDeregistration();
		SubmitCollisionDeregistration<flimSound>(this);
	}

}

errcode flimSound::Update()
{
	if (occlusionEnabled)
	{
		Matrix mat(Matrix(SCALE, 4000.0f,4000.0f,4000.0f) * Matrix(TRANS, this->position));
		UpdateCollisionData(mat);

		// put down for viewing
		Vect v1(FlimListener::GetPosition().X(), FlimListener::GetPosition().Y() - 1.0f, FlimListener::GetPosition().Z());

		Visualizer::ShowLine(position, v1, flimColor::blue);
	}

	return errcode::success;
}



errcode flimSound::Collision(GameObject *)
{
	//Trace::out("occluding");
	return errcode::success;
}

errcode flimSound::CollisionTerrain(const CollisionVolumeAABB & )
{

	this->filter.ActivateFilter(FilterType::LoPass);

	this->filter.SetCutoff(500.0f);

	return errcode::success;
}

errcode flimSound::CollisionEnter(Collidable *)
{
	this->filter.ActivateFilter(FilterType::LoPass);

	this->filter.SetCutoff(500.0f);

	return errcode::success;
}

errcode flimSound::CollisionExit()
{
	this->filter.DeactivateFilter(FilterType::LoPass);

	this->filter.SetCutoff(22000.0f);

	return errcode::success;
}






errcode flimSound::SetReverbLevel(float level)
{
	this->snd->SetReverbLevel(level);


	return errcode::success;
}

errcode flimSound::SetReverbTime(float time)
{
	this->snd->SetReverbTime(time);
	return errcode::success;
}

errcode flimSound::SetReverbPreDelay(float time)
{
	this->snd->SetReverbPreDelay(time);
	return errcode::success;
}

errcode flimSound::SetReverbSize(float size)
{
	this->snd->SetReverbSize(size);
	return errcode::success;
}

errcode flimSound::SetReverbDensity(float density)
{
	this->snd->SetReverbDensity(density);
	return errcode::success;
}

errcode flimSound::SetReverbPreset(flimReverb _reverb)
{
	this->snd->SetReverbPreset(_reverb);
	return errcode::success;
}





snd_err flimSound::getPosition(Vect & out) const
{
	out = this->position;
	return snd_err::OK;
}

snd_err flimSound::setPosition(const Vect & pos)
{
	if (is3D && FlimMath::DifferentEnough(this->position, pos, 2.0f))
	{
		this->position = pos;
		this->snd->setPosition(pos);
	}
	return snd_err::OK;
}

snd_err flimSound::SetOrientation(const Vect& vect, float xU, float yU, float zU)
{
	snd_err err = snd_err::OK;
	if (is3D)
	{
		this->snd->setOrientation(vect, xU, yU, zU);
	}

	return err;
}

snd_err flimSound::getFilter(flimFilter & out) const
{
	out = this->filter;
	return snd_err::OK;
}

snd_err flimSound::Pan(float p, int triggerTime)
{
	this->snd->Pan(p, triggerTime);
	return snd_err::OK;
}

snd_err flimSound::Pan(float from, float to, float time, int triggerTime)
{
	this->snd->Pan(from, to, time, triggerTime);	
	return snd_err::OK;
}

snd_err flimSound::Loop(bool toLoop, int triggerTime)
{
	this->snd->Loop(toLoop, triggerTime);
	return snd_err::OK;
}

snd_err flimSound::Pitch(float p, int triggerTime)
{
	this->snd->Pitch(p, triggerTime);
	return snd_err::OK;
}

snd_err flimSound::Pitch(float from, float to, float time, int triggerTime)
{
	this->snd->Pitch(from, to, time, triggerTime);
	return snd_err::OK;
}

snd_err flimSound::Volume(float p, int triggerTime)
{
	this->snd->Volume(p, triggerTime);
	return snd_err::OK;
}

snd_err flimSound::Volume(float from, float to, float time, int triggerTime)
{
	this->snd->Volume(from, to, time, triggerTime);
	return snd_err::OK;
}

snd_err flimSound::Play(bool toLoop, int t, int _priority)
{
	//SoundEngine::CreateSoundCall(this->snd, sndID);
	this->snd->Play(toLoop, t, _priority);
	if (is3D)
	{
		this->snd->setPosition(position);
	}


	return snd_err::OK;
}

snd_err flimSound::Stop(int t)
{
	this->snd->Stop(t);
	return snd_err::OK;
}

snd_err flimSound::Pause(int t)
{
	this->snd->Pause(t);
	return snd_err::OK;
}

snd_err flimSound::IsPlaying(bool & out)
{
	this->snd->IsPlaying(out);

	return snd_err::OK;
}

snd_err flimSound::GetTimeSinceStarted(int & time)
{
	this->snd->GetTimeSinceStarted(time);
	return snd_err::OK;
}

snd_err flimSound::GetVolume(float & vol)
{
	this->snd->GetVolume(vol);
	return snd_err::OK;
}

snd_err flimSound::GetPitch(float & p)
{
	this->snd->GetPitch(p);
	return snd_err::OK;
}

snd_err flimSound::GetPan(float & p)
{
	this->snd->GetPan(p);
	return snd_err::OK;
}

snd_err flimSound::GetPriority(int & p)
{
	this->snd->GetPriority(p);
	return snd_err::OK;
}

snd_err flimSound::GetLoop(bool & loop)
{
	this->snd->GetLoop(loop);
	return snd_err::OK;
}

snd_err flimSound::SubmitSoundEndedCallback(CallbackCommand * cmd)
{
	this->snd->SubmitSoundEndedCallback(cmd);
	return snd_err::OK;
}
