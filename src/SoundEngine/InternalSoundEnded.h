#pragma once
#ifndef INTERNALSOUNDENDED_H
#define INTERNALSOUNDENDED_H

#include "CallbackCommand.h"
class Playlist;

class InternalSoundEnded : public CallbackCommand // playlist submits this callback to the longest sound attached
{
public:
	//big four
	InternalSoundEnded() = delete;
	InternalSoundEnded(const InternalSoundEnded&) = default;
	InternalSoundEnded& operator=(const InternalSoundEnded&) = default;
	~InternalSoundEnded() {
		//DebugMsg::out("Internal sound ended CallbackCommand Cleaned\n");
	};

	InternalSoundEnded(Playlist* p);

	void execute() override;

	virtual InternalSoundEnded* clone() override;

private:
	Playlist* playlist;


};

#endif