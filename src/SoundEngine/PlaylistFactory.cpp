#include "PlaylistFactory.h"
#include "Playlist.h"
#include "PlaylistInitCommand.h"

#include "SoundManager.h"

#include "SoundEngine.h"

PlaylistFactory::PlaylistFactory(std::list<PlaylistInitializationCommand*> cmds, SoundCallID _id) : initCommands(cmds), id(_id)
{
	// make a bunch of them on construction. IDK... nested while loop? should be good as long as playlists are frontloaded
}

PlaylistFactory::~PlaylistFactory()
{
	/*
	std::list<PlaylistInitializationCommand*>::iterator cmdIter = initCommands.begin();
	while (cmdIter != initCommands.end())
	{
		delete (*cmdIter);
		(*cmdIter) = nullptr;
		cmdIter++;
	}
	*/


	// active playlists
	std::list<Playlist*>::iterator poolIter = activePool.begin();
	while (poolIter != activePool.end())
	{
		delete(*poolIter);
		(*poolIter) = nullptr;
		poolIter++;
	}

	// inactive playlists
	while (!inactivePool.empty())
	{
		delete inactivePool.top();
		inactivePool.pop();
	}
	

}

snd_err PlaylistFactory::CreatePlaylist(Playlist *& out, unsigned int instance, bool _3D)
{
	snd_err err = snd_err::OK;

	if (inactivePool.empty()) //...gotta make one!
	{
		out = new Playlist(id, instance, _3D);

		// got the empty playlist, now fill it out
		std::list<PlaylistInitializationCommand*>::iterator iter = initCommands.begin();
		while (iter != initCommands.end())
		{
			// give the command a context
			err = (*iter)->AttachPlaylist(out);
			// execute on that context
			(*iter)->execute();
			iter++;
		}

	}
	else
	{
		// these playlists are already filled out from previous use so it's cool!
		out = inactivePool.top();
		inactivePool.pop();
	}

	activePool.push_back(out);

	return err;
}

snd_err PlaylistFactory::ReturnPlaylist(Playlist * toReturn)
{
	snd_err err = snd_err::OK;
	if (toReturn)
	{
		activePool.remove(toReturn);
		inactivePool.push(toReturn);
	}
	else
	{
		err = snd_err::ERR;
	}
	
	return err;
}
