#include "PlaylistManager.h"
#include "PlaylistFactory.h"
#include "SoundCallRegistry.h"

#include "PlaylistAddCommand.h"
#include "PlaylistAddSoundCommand.h"
#include "PlaylistAddCallbackCommand.h"
#include "Playlist.h"


#include "HashThis.h"

#include "PlayCmd.h"
#include "PanCmd.h"
#include "LoopCommand.h"
#include "PitchCommand.h"
#include "VolumeCommand.h"
#include "SoundManager.h"
#include "AudioMain.h"
#include "TransitionOnEnd.h"
#include "AssignCallbackCommand.h"

#include <string>
#include <algorithm>
PlaylistManager* PlaylistManager::instance = nullptr;

// helpers
snd_err SaveCharBuffer(const char* path_to_script, char* & outBuffer);
std::list<PlaylistInitializationCommand*> ParseScript(const char* path_to_script, void(*cb)(void));
std::string ParseSoundFile(std::string toParse, unsigned int &outKey);
std::string ParseCommandType(std::string toParse, int& outTime, ThreadCommandType& outCmdType);

PlayCommand* ParsePlay(std::string toParse, unsigned int& outID);
PanCommand* ParsePan(std::string toParse, unsigned int& outID);
PitchCommand* ParsePitch(std::string toParse, unsigned int& outID);
VolumeCommand* ParseVolume(std::string toParse, unsigned int& outID);
LoopCommand* ParseLoop(std::string toParse, unsigned int& outID);
TransitionOnEnd* ParseTransition(std::string toParse, unsigned int& id1, unsigned int& id2);

PlaylistDescriptor::~PlaylistDescriptor()
{
	if (factory)
	{
		delete factory;
		factory = nullptr;
	}
}

PlaylistManager::PlaylistManager()
{

}

PlaylistManager::~PlaylistManager()
{
}

// Initialize PlaylistDescriptor(const char* path_to_script, SoundCallID)
// --parses file
// --populates a list of PlaylistInitializationCommands via that data
// -- constructs a new PlaylistFactory with the SoundCallID and that list

snd_err PlaylistManager::privInitializePlaylistDescriptor(std::string path_to_script, SoundCallID id, void(*cb)(void))
{
	snd_err err = snd_err::OK;

	//loading audio needs to be async... with a callback
	// load sounds -----------
	std::list<PlaylistInitializationCommand*> cmds = ParseScript(path_to_script.c_str(), cb);

	PlaylistDescriptor* desc = new PlaylistDescriptor();
	desc->playlistID = id;
	desc->factory = new PlaylistFactory(cmds, id);

	this->playlistDescriptors.push_back(desc);

	return err;
}

// short cut method so you can only use the sound engine with sound files rather than scripts
snd_err PlaylistManager::privInitializePlaylistDescriptor_SingleSound(std::string path_to_script, SoundCallID id, void(*cb)(void))
{
	snd_err err = snd_err::OK;

	//loading audio needs to be async... with a callback
	// load sounds -----------
	std::list<PlaylistInitializationCommand*> cmds;

	unsigned int snd_id = HashThis(path_to_script.c_str());
	cmds.push_back(new PlaylistAddSoundCommand(snd_id, path_to_script.c_str(), cb));
	PlayCommand* playCmd = new PlayCommand();
	cmds.push_back(new PlaylistAddCommand(playCmd, 0, snd_id));

	PlaylistDescriptor* desc = new PlaylistDescriptor();
	desc->playlistID = id;
	desc->factory = new PlaylistFactory(cmds, id);

	this->playlistDescriptors.push_back(desc);

	return err;
}

std::list<PlaylistInitializationCommand*> ParseScript(const char* path_to_script, void(*cb)(void))
{
	// read file into char buffer
	char* buffer = nullptr;
	// we do the actual parsing of a char buffer
	SaveCharBuffer(path_to_script, buffer);
	assert(buffer);

	// STL strings are easier for right now...
	std::string strBuf(buffer);

	// the list to output and give to playlist factory
	std::list<PlaylistInitializationCommand*> cmdList;

	// the holder for the string to pass to the factory to get commands
	std::string input = "";

	// the playhead to move down the character stream
	unsigned int delineatorStart = 0;
	unsigned int delineatorEnd = 0;

	// parse the list of sounds
	delineatorStart = strBuf.find("<SOUND>");
	delineatorEnd = strBuf.find("</SOUND_LIST>");
	std::string soundList = strBuf.substr(delineatorStart, delineatorEnd - 14);

	soundList.erase(std::remove(soundList.begin(), soundList.end(), '\n'), soundList.end());
	soundList.erase(std::remove(soundList.begin(), soundList.end(), '\r'), soundList.end());

	while (delineatorEnd != soundList.npos) // does this condition work?
	{
		delineatorStart = 0;
		delineatorEnd = 0;
		PlaylistAddSoundCommand* newCommand = nullptr;


		delineatorEnd = soundList.find("</SOUND>");
		std::string check(soundList.substr(0, delineatorEnd));
		
		// goes a level deeper and get the guy here
		unsigned int key = 0;
		std::string path = ParseSoundFile(check, key);
		//assert(key);
		//assert(path);
		if (path.size() > 0)
		{
			newCommand = new PlaylistAddSoundCommand(key, path.c_str(), cb);
			cmdList.push_back(newCommand);
		}

		soundList.erase(0, delineatorEnd + 8);
	}
	// now parse the commands out of this mess...
 	// parse the list of sounds
	delineatorStart = strBuf.find("<COMMAND>");
	delineatorEnd = strBuf.find("</COMMAND_LIST>");
	std::string commandList = strBuf.substr(delineatorStart, delineatorEnd - 14);

	commandList.erase(std::remove(commandList.begin(), commandList.end(), '\n'), commandList.end());
	commandList.erase(std::remove(commandList.begin(), commandList.end(), '\r'), commandList.end());

	while (delineatorEnd != commandList.npos)
	{
		delineatorStart = 0;
		delineatorEnd = 0;

		// second tag of first command
		delineatorEnd = commandList.find("</COMMAND>");
		std::string check(commandList.substr(0, delineatorEnd));

		// first get the type and the time, then switch to find out what you need to do
		ThreadCommandType cmdType;
		int executionTime;
		std::string params = ParseCommandType(check, executionTime, cmdType);

		switch (cmdType)
		{
			case ThreadCommandType::Play:
			{
				unsigned int soundToPlay;
				//parse remaining string to get those params
				PlayCommand* playCmd = ParsePlay(params, soundToPlay);
				cmdList.push_back(new PlaylistAddCommand(playCmd, executionTime, soundToPlay)); // oh my GOD
				
				break;
			}
			case ThreadCommandType::Pause:
			{
				// params
				std::string soundToPause;

				//parse remaining string to get those params
				break;
			}
			case ThreadCommandType::Stop:
			{
				// params
				std::string soundToStop;

				//parse remaining string to get those params
				break;
			}
			case ThreadCommandType::Pan:
			{
				// params
				unsigned int soundToPan;
				//parse remaining string to get those params
				PanCommand* panCmd = ParsePan(params, soundToPan);
				cmdList.push_back(new PlaylistAddCommand(panCmd, executionTime, soundToPan)); // oh my GOD
				break;
			}
			case ThreadCommandType::Pitch:
			{
				// params
				unsigned int soundToPitch;
				//parse remaining string to get those params
				PitchCommand* pitchCmd = ParsePitch(params, soundToPitch);
				cmdList.push_back(new PlaylistAddCommand(pitchCmd, executionTime, soundToPitch)); // oh my GOD
				break;
			}
			case ThreadCommandType::Volume:
			{
				// params
				unsigned int soundToVolume;
				//parse remaining string to get those params
				VolumeCommand* VolumeCmd = ParseVolume(params, soundToVolume);
				cmdList.push_back(new PlaylistAddCommand(VolumeCmd, executionTime, soundToVolume)); // oh my GOD
				break;
			}
			case ThreadCommandType::CallbackSoundEnded:
			{
				unsigned int id1 = 0x0;
				unsigned int id2 = 0x0;
				TransitionOnEnd* transition = ParseTransition(params, id1, id2);
				cmdList.push_back(new PlaylistAddCallbackCommand(transition, executionTime, id1, id2));
				break;
			}
		}

		commandList.erase(0, delineatorEnd + 10);
	}
	
	return cmdList;

}

// expects <SOUND>key : path</SOUND>
std::string ParseSoundFile(std::string toParse, unsigned int &outKey)
{
	// 7 characters in <SOUND>
	toParse.erase(0, 7);
	size_t delineator = toParse.find(" : ");

	std::string check(toParse.substr(0, delineator).c_str());
	check;
	outKey = HashThis(toParse.substr(0, delineator).c_str());
	toParse.erase(0, delineator + 3);
	return toParse;
}

// gets the time and type and returns a cleaned string to pass to the case-by-case scenarios..
std::string ParseCommandType(std::string toParse, int& outTime, ThreadCommandType& outCmdType)
{
	// 7 characters in <COMMAND>
	toParse.erase(0, 9);
	size_t delineator = toParse.find(" ");

	std::string check(toParse.substr(0, delineator).c_str());
	outTime = atoi(check.c_str());
	toParse.erase(0, delineator + 1);

	// now get the param name, hash the string, and cast the hash to a command type
	delineator = toParse.find("(");
	std::string checkCmd(toParse.substr(0, delineator));
	unsigned int threadCommandHash = HashThis(checkCmd.c_str());
	outCmdType = (ThreadCommandType)(threadCommandHash);

	// lob off the rest of the string so the either guys just get the easy stuff
	//delineator = toParse.find("</");
	//toParse.erase(delineator);

	return toParse;
}

// output a command and an ID to associate to it
// sees Play(stringID)
PlayCommand * ParsePlay(std::string toParse, unsigned int& outID)
{
	// remove parens
	size_t delineator = toParse.find("(");
	toParse.erase(0, delineator + 1);
	delineator = toParse.find(")");
	toParse.erase(delineator);

	// hash it, assign it to the output!
	outID = HashThis(toParse.c_str());
	return (new PlayCommand());
}

// output a command and an ID to associate to it
// sees Play(stringID)
TransitionOnEnd * ParseTransition(std::string toParse, unsigned int& id1, unsigned int& id2)
{

	// remove parens
	size_t delineator = toParse.find("(");
	toParse.erase(0, delineator + 1);
	delineator = toParse.find(")");
	toParse.erase(delineator);

	// get ID1
	delineator = toParse.find(",");
	std::string checkID(toParse.substr(0, delineator));
	id1 = HashThis(checkID.c_str());
	toParse.erase(0, delineator + 1);

	//get ID2
	delineator = toParse.find(", ");
	std::string checkFrom(toParse.substr(1, delineator));
	id2 = HashThis(checkFrom.c_str());
	toParse.erase(0, delineator + 1);

	return new TransitionOnEnd(checkFrom.c_str());
}

// output a command and an ID to associate to it
PanCommand * ParsePan(std::string toParse, unsigned int& outID)
{
	float from = 0.0f;
	float to = 0.0f;
	float delta = 0.0f;

	// remove parens
	size_t delineator = toParse.find("(");
	toParse.erase(0, delineator + 1);
	delineator = toParse.find(")");
	toParse.erase(delineator);

	// get ID
	delineator = toParse.find(",");
	std::string checkID(toParse.substr(0, delineator));
	outID = HashThis(checkID.c_str());
	toParse.erase(0, delineator + 1);

	//get from
	delineator = toParse.find(",");
	std::string checkFrom(toParse.substr(0, delineator));
	from = std::stof(checkFrom);
	toParse.erase(0, delineator + 1);

	// get to
	delineator = toParse.find(",");
	std::string checkTo(toParse.substr(0, delineator));
	to = std::stof(checkTo);
	toParse.erase(0, delineator + 1);

	// get delta
	delineator = toParse.find(",");
	std::string checkDelta(toParse.substr(0, delineator));
	delta = std::stof(checkDelta);
	toParse.erase(0, delineator + 1);

	return new PanCommand(from, to, delta);
}

// output a command and an ID to associate to it
PitchCommand * ParsePitch(std::string toParse, unsigned int& outID)
{
	float from = 0.0f;
	float to = 0.0f;
	float delta = 0.0f;

	// remove parens
	size_t delineator = toParse.find("(");
	toParse.erase(0, delineator + 1);
	delineator = toParse.find(")");
	toParse.erase(delineator);

	// get ID
	delineator = toParse.find(",");
	std::string checkID(toParse.substr(0, delineator));
	outID = HashThis(checkID.c_str());
	toParse.erase(0, delineator + 1);

	//get from
	delineator = toParse.find(",");
	std::string checkFrom(toParse.substr(0, delineator));
	from = std::stof(checkFrom);
	toParse.erase(0, delineator + 1);

	// get to
	delineator = toParse.find(",");
	std::string checkTo(toParse.substr(0, delineator));
	to = std::stof(checkTo);
	toParse.erase(0, delineator + 1);

	// get delta
	delineator = toParse.find(",");
	std::string checkDelta(toParse.substr(0, delineator));
	delta = std::stof(checkDelta);
	toParse.erase(0, delineator + 1);

	return new PitchCommand(from, to, delta);
}

// output a command and an ID to associate to it
VolumeCommand * ParseVolume(std::string toParse, unsigned int& outID)
{
	float from = 0.0f;
	float to = 0.0f;
	float delta = 0.0f;

	// remove parens
	size_t delineator = toParse.find("(");
	toParse.erase(0, delineator + 1);
	delineator = toParse.find(")");
	toParse.erase(delineator);

	// get ID
	delineator = toParse.find(",");
	std::string checkID(toParse.substr(0, delineator));
	outID = HashThis(checkID.c_str());
	toParse.erase(0, delineator + 1);

	//get from
	delineator = toParse.find(",");
	std::string checkFrom(toParse.substr(0, delineator));
	from = std::stof(checkFrom);
	toParse.erase(0, delineator + 1);

	// get to
	delineator = toParse.find(",");
	std::string checkTo(toParse.substr(0, delineator));
	to = std::stof(checkTo);
	toParse.erase(0, delineator + 1);

	// get delta
	delineator = toParse.find(",");
	std::string checkDelta(toParse.substr(0, delineator));
	delta = std::stof(checkDelta);
	toParse.erase(0, delineator + 1);

	return new VolumeCommand(from, to, delta);
}

// output a command and an ID to associate to it
LoopCommand * ParseLoop(std::string toParse, unsigned int& outID)
{
	toParse;
	outID;
	return nullptr;
}


snd_err SaveCharBuffer(const char* path_to_script, char* & outBuffer)
{

	FILE* pFout = nullptr;

	errno_t err = fopen_s(&pFout, path_to_script, "rb");
	err;
	//get the size!
	// seeks to end
	fseek(pFout, 0, SEEK_END);

	// position of head will tell the size of the file
	unsigned int size = ftell(pFout);

	//make a char buffer of that size
	char* buffer = new char[size];

	// move head back to the top
	rewind(pFout);

	// copy the contents of the file into the buffer you made
	fread(buffer, size, 1, pFout);

	fclose(pFout);

	buffer[size] = 0; // null terminate it!
	/* maybe keep this?
	for (unsigned int i = 0; i < size; i++)
	{
		buffer[i] = tolower(buffer[i]); // at least it's not case sensitive now
	}
	*/
	outBuffer = buffer;

	return snd_err::OK;
}


// StartPlaylist(SoundCallID, HandleID)
// -- finds associated factory
// -- gets a new playlist (factory creates it by firing off the list of initialization commands)
// -- gives the playlist its instance number via the handle ID 
// -- adds new playlist to list of active playlists
snd_err PlaylistManager::privStartPlaylist(SoundCallID id, unsigned int handle, bool is3D)
{
	snd_err err = snd_err::ERR;

	std::list<PlaylistDescriptor*>::iterator iter = this->playlistDescriptors.begin();

	while (iter != playlistDescriptors.end())
	{
		if ((*iter)->playlistID == id)
		{
			Playlist* playlist = nullptr;
			(*iter)->factory->CreatePlaylist(playlist, handle, is3D);
			assert(playlist);

			this->activePlaylists.push_back(playlist);
			//playlist->Play();

			err = snd_err::OK;
			return err;
		}
		iter++;
	}

	return err;
}


// StopPlaylist(HandleID)
// -- searches active playlist for the instance associated with that handle
// -- calls stop on it, returns it to the factory
snd_err PlaylistManager::privStopPlaylist(unsigned int handle)
{
	snd_err err = snd_err::NOT_FOUND;

	std::list<Playlist*>::iterator iter = activePlaylists.begin();
	while (iter != activePlaylists.end())
	{
		if ((*iter)->GetInstanceNumber() == handle)
		{
			(*iter)->Stop();
			err = snd_err::OK;
		}
		iter++;
	}

	return err;
}

snd_err PlaylistManager::privGetPlaylist(Playlist *& p, unsigned int handle)
{
	snd_err err = snd_err::NOT_FOUND;

	std::list<Playlist*>::iterator iter = activePlaylists.begin();
	while (iter != activePlaylists.end())
	{
		if ((*iter)->GetInstanceNumber() == handle)
		{
			p = (*iter);
			err = snd_err::OK;
		}
		iter++;
	}

	return err;
}

snd_err PlaylistManager::privTerminate()
{
	// clean out list of descriptors
	snd_err err = snd_err::OK;

	
	std::list<PlaylistDescriptor*>::iterator pdIter = playlistDescriptors.begin();
	while (pdIter != playlistDescriptors.end())
	{
		delete (*pdIter);
		pdIter++;
	}

	/*
	std::list<Playlist*>::iterator playlistIter = activePlaylists.begin();
	while (playlistIter != activePlaylists.end())
	{
		delete (*playlistIter);
		playlistIter++;
	}
	*/
	
	return err;
}