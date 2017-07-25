#pragma once
#ifndef AUDIOCOMMANDFACTORY_H
#define AUDIOCOMMANDFACTORY_H

class AudioThreadCommand;
class AudioCommandType;
class AudioCommandFactory
{
public:
	AudioThreadCommand* Create(AudioCommandType* obj);
};

#endif