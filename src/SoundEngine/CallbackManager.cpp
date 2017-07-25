#include "CallbackManager.h"
#include "CallbackCommand.h"




CallbackMailbox::CallbackMailbox()
{

	// create brokers
	int i = 0;
	while (i < NUM_VALID_CALLBACK_TYPES)
	{
		this->callbackBrokers.insert(std::pair<CMDTYPES, SoundExecutioner*>((CMDTYPES)(i), new SoundExecutioner()));
		i++;
	}

}

snd_err CallbackMailbox::Terminate()
{
	
	std::map<CMDTYPES, SoundExecutioner*>::iterator iter = callbackBrokers.begin();
	while (iter != callbackBrokers.end())
	{
		if (iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
		}
		else
		{
			return snd_err::ERR;
		}
		iter++;
	}
	callbackBrokers.clear();
	
	
	return snd_err::OK;
}

CallbackMailbox::~CallbackMailbox()
{
	
	// free brokers
	std::map<CMDTYPES, SoundExecutioner*>::iterator iter = callbackBrokers.begin();
	while (iter != callbackBrokers.end())
	{
		if (iter->second)
		{
			delete iter->second;
			iter->second = nullptr;
			iter++;
		}
		else
		{
			assert(false);
		}
	}
	
	callbackBrokers.clear();
}

snd_err CallbackMailbox::SubmitCallback(CallbackCommand * cmd)
{
	snd_err err = snd_err::OK;
	if (cmd->commandType != CMDTYPES::NO_TYPE)
	{
		this->callbackBrokers.at(cmd->commandType)->addCommand(cmd);
	}
	else
	{
		err = snd_err::ERR;
	}
	return err;
}

VoiceCallback* CallbackMailbox::GetCallbacks()
{
	return (VoiceCallback*)(this);
}

void CallbackMailbox::OnStreamEnd()
{
	callbackBrokers.at(CMDTYPES::STREAM_END)->ProcessDeferredCommands();
	callbackBrokers.at(CMDTYPES::STREAM_END)->ProcessInstantCommands();
}

void CallbackMailbox::OnVoiceProcessingPassEnd()
{
	callbackBrokers.at(CMDTYPES::VOICE_PROCESSING_PASS_END)->ProcessDeferredCommands();
	callbackBrokers.at(CMDTYPES::VOICE_PROCESSING_PASS_END)->ProcessInstantCommands();
}

void CallbackMailbox::OnVoiceProcessingPassStart(UINT32 SamplesRequired)
{
	SamplesRequired;
	callbackBrokers.at(CMDTYPES::VOICE_PROCESSING_PASS_START)->ProcessDeferredCommands();
	callbackBrokers.at(CMDTYPES::VOICE_PROCESSING_PASS_START)->ProcessInstantCommands();
}

void CallbackMailbox::OnBufferEnd(void * pBufferContext)
{
	pBufferContext;
	callbackBrokers.at(CMDTYPES::BUFFER_END)->ProcessDeferredCommands();
	callbackBrokers.at(CMDTYPES::BUFFER_END)->ProcessInstantCommands();
}

void CallbackMailbox::OnBufferStart(void * pBufferContext)
{
	pBufferContext;
	callbackBrokers.at(CMDTYPES::BUFFER_START)->ProcessDeferredCommands();
	callbackBrokers.at(CMDTYPES::BUFFER_START)->ProcessInstantCommands();
}

void CallbackMailbox::OnLoopEnd(void * pBufferContext)
{
	pBufferContext;
	callbackBrokers.at(CMDTYPES::LOOP_END)->ProcessDeferredCommands();
	callbackBrokers.at(CMDTYPES::LOOP_END)->ProcessInstantCommands();
}

void CallbackMailbox::OnVoiceError(void * pBufferContext, HRESULT Error)
{
	pBufferContext;
	Error;
	callbackBrokers.at(CMDTYPES::VOICE_ERROR)->ProcessDeferredCommands();
	callbackBrokers.at(CMDTYPES::VOICE_ERROR)->ProcessInstantCommands();
}
