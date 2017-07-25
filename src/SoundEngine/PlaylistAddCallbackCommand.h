#pragma once
#ifndef PlaylistAddCB_H
#define PlaylistAddCB_H

#include "PlaylistInitCommand.h"
#include "snd_err.h"

class Playlist;
class CallbackCommand;

class PlaylistAddCallbackCommand : public PlaylistInitializationCommand
{
public:
	PlaylistAddCallbackCommand() = delete;
	PlaylistAddCallbackCommand(CallbackCommand* cmd, int time, unsigned int id1, unsigned int id2 = 0);
	PlaylistAddCallbackCommand(CallbackCommand* cmd, int time, unsigned int id1);
	virtual ~PlaylistAddCallbackCommand() {
		//DebugMsg::out("PlaylistAddCallback Command Cleaned\n");
	};
	PlaylistAddCallbackCommand& operator=(const PlaylistAddCallbackCommand&) = default;
	PlaylistAddCallbackCommand(const PlaylistAddCallbackCommand&) = default;


	virtual snd_err AttachPlaylist(Playlist*);
	virtual void execute();

private:
	CallbackCommand* cmd;
	int time;
	unsigned int id;
	unsigned int secondaryID;
	Playlist* playlist;


};

#endif