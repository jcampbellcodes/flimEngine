#include "flimFilter.h"
#include "SoundCall.h"
#include "CircularData.h"
#include "SoundEngine.h"
#include "AudioCommandTypes\ActivateFilterType.h"
#include "AudioCommandTypes\DeactivateFilterType.h"
#include "AudioCommandTypes\SetCutoffType.h"

flimFilter::flimFilter(SoundCall * sndCall) : snd(sndCall)
{
}

snd_err flimFilter::ActivateFilter(FilterType type)
{
	ThreadCommand cmd;
	cmd.type = new ActivateFilterType();
	cmd.handle = snd->GetHandleNo();
	cmd.filterType = type;

	CircularData* pOut = SoundEngine::GetG2ABuff();

	pOut->PushBack(cmd);

	return snd_err::OK;
}

snd_err flimFilter::DeactivateFilter(FilterType type)
{
	ThreadCommand cmd;
	cmd.type = new DeactivateFilterType();
	cmd.handle = snd->GetHandleNo();
	cmd.filterType = type;

	CircularData* pOut = SoundEngine::GetG2ABuff();

	pOut->PushBack(cmd);
	return snd_err::OK;
}

snd_err flimFilter::SetCutoff(float cutoff)
{
	ThreadCommand cmd;
	cmd.type = new SetCutoffType();
	cmd.handle = snd->GetHandleNo();
	cmd.filterCutoff = cutoff;

	CircularData* pOut = SoundEngine::GetG2ABuff();

	pOut->PushBack(cmd);
	return snd_err::OK;
}

snd_err flimFilter::GetCutoff(float & )
{
	// unfinished
	return snd_err::OK;
}
