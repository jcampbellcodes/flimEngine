#pragma once
#ifndef IndividualSOUNDENDED_H
#define IndividualSOUNDENDED_H

#include "CallbackCommand.h"
class Playlist;

class IndividualSoundEnded : public CallbackCommand // playlist submits this callback to the longest sound attached
{
public:
	//big four
	IndividualSoundEnded() = delete;
	IndividualSoundEnded(const IndividualSoundEnded&) = default;
	IndividualSoundEnded& operator=(const IndividualSoundEnded&) = default;
	~IndividualSoundEnded() {
		//DebugMsg::out("Individual sound ended CallbackCommand Cleaned\n");
	};

	IndividualSoundEnded(Playlist* p);

	void execute() override;

	virtual IndividualSoundEnded* clone() override;

private:
	Playlist* playlist;


};

#endif