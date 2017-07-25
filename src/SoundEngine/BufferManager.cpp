#include "BufferManager.h"
#include "VoiceManager.h"
#include <assert.h>
//#include <xaudio2.h>
#include "AzulCore.h"
#include "HashThis.h"
#include "SoundManager.h"
#include "ThreadCommands.h"
#include "SoundCallRegistry.h"
#include "HashThis.h"

#include "AudioCommandTypes\LoadWaveType.h"


BufferManager* BufferManager::instance = nullptr;

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void * buf, DWORD buffersize, DWORD bufferoffset);

BufferManager::BufferManager() : activeList(new BufferList()), inactiveList(new BufferList())
{
}


BufferManager::~BufferManager()
{
	if (activeList)
	{
		delete activeList;
	}
	if (inactiveList)
	{
		delete inactiveList;
	}
	//DebugMsg::out("Buffer Manager cleaned\n");
}





/***************************************************************/


/*                  Private Implementation                     */



/***************************************************************/




snd_err BufferManager::privAdd(const char * input, const char * path, void(*cb)(void))
{
	snd_err err;
	// first check that the node is not in the inactive list
	BufferNode* node = nullptr;

	unsigned int md5 = HashThis(input);
	if (activeList->Find(node, md5) == snd_err::NOT_FOUND) // sanity check
	{
		if (inactiveList->Find(node, md5) == snd_err::NOT_FOUND) // then load it!
		{
			//sanity check
			assert(!node);
			//XAUDIO2_BUFFER buffer;
			//WAVEFORMATEXTENSIBLE wfx;
			//err = Load(wfx, buffer, path);

			// insert (MD5, buffer ptr) into a new list
			// makes buffer node with nullptrs
			node = new BufferNode(md5);

			//asks file thread to load it, gives it the node, and file thread adds that to node on its time
			ThreadCommand cmd;
			cmd.type = new LoadWaveType();
			cmd.bufferNode = node;
			cmd.handle = md5;
			cmd.wavePath = path;
			cmd.loadedCallback = cb;
			SoundManager::SendDataA2F(cmd);


			assert(node);
		}
		// otherwise, it was found in the inactive list and set internally
		assert(node);

		err = activeList->Add(node);
	}
	else
	{
		err = snd_err::MULTIPLE_ADD;
	}

	return err;
}

// if they already have the hash
snd_err BufferManager::privAdd(unsigned int input, const char * path, void(* cb)(void))
{
	snd_err err;
	// first check that the node is not in the inactive list
	BufferNode* node = nullptr;

	unsigned int md5 = input;
	if (activeList->Find(node, md5) == snd_err::NOT_FOUND) // sanity check
	{
		if (inactiveList->Find(node, md5) == snd_err::NOT_FOUND) // then load it!
		{
			//sanity check
			assert(!node);
			//XAUDIO2_BUFFER buffer;
			//WAVEFORMATEXTENSIBLE wfx;
			//err = Load(wfx, buffer, path);

			// insert (MD5, buffer ptr) into a new list
			node = new BufferNode(md5);



			//asks file thread to load it, gives it the node, and file thread adds that to node on its time
			ThreadCommand cmd;
			cmd.type = new LoadWaveType();
			cmd.bufferNode = node;
			cmd.handle = md5;
			cmd.wavePath = std::string(path);
			cmd.loadedCallback = cb;
			SoundManager::SendDataA2F(cmd);



			assert(node);
		}
		// otherwise, it was found in the inactive list and set internally
		assert(node);

		err = activeList->Add(node);
	}
	else
	{
		err = snd_err::MULTIPLE_ADD;
	}

	return err;
}

snd_err BufferManager::privRemove(const char * input)
{
	snd_err err;

	// hash input to MD5	
	unsigned int md5 = HashThis(input);

	BufferNode* node = nullptr;
	// search 
	err = Find(node, md5);
	assert(node);

	// reference counting
	if (node->InUse() == snd_err::NOT_IN_USE)
	{
		activeList->Remove(node);
		inactiveList->Add(node);
	}
	else
	{
		node->RemoveRef();
	}

	return snd_err::OK;
}

snd_err BufferManager::privRemove(unsigned int md5)
{
	snd_err err;
	BufferNode* node = nullptr;
	// search 
	err = Find(node, md5);
	assert(node);

	// reference counting
	node->RemoveRef();
	if (node->InUse() == snd_err::NOT_IN_USE)
	{
		activeList->Remove(node);
		//inactiveList->Add(node);
	}

	return snd_err::OK;
}

// getting node
// add to reference count here
snd_err BufferManager::privFind(const char * input, XAUDIO2_BUFFER *& out, WAVEFORMATEXTENSIBLE*& wfx)
{
	unsigned int md5 = HashThis(input);

	snd_err err;
	BufferNode* node = nullptr;
	// search 
	err = Find(node, md5); //internal find
	
	if (!node)
	{
		return err;
	}


	// BLOCKING!!!!!! FIND A BETTER WAY, ASS
	int lol = 0;
	while (!node->buffer)
	{
		lol++;
	}

	while (!node->wfx)
	{
		lol++;
	}

	out = node->buffer;
	wfx = node->wfx;


	// add to reference count
	node->AddRef();

	return err;
}

// getting node
// add to reference count here
snd_err BufferManager::privFind(unsigned int input, XAUDIO2_BUFFER *& out, WAVEFORMATEXTENSIBLE*& wfx)
{
	unsigned int md5 = input;

	snd_err err;
	BufferNode* node = nullptr;
	// search 
	err = Find(node, md5); //internal find

	if (!node)
	{
		return err;
	}

	// BLOCKING!!!!!! FIND A BETTER WAY, ASS
	int lol = 0;
	while (!node->buffer)
	{
		lol++;
	}

	while (!node->wfx)
	{
		lol++;
	}

	out = node->buffer;
	wfx = node->wfx;


	// add to reference count
	node->AddRef();

	return err;
}

snd_err BufferManager::privTerminate()
{
	snd_err err = snd_err::OK;
	if (activeList)
	{
		delete activeList;
	}
	if (inactiveList)
	{
		delete inactiveList;
	}

	return err;
}

// internal find
snd_err BufferManager::Find(BufferNode *& out, unsigned int md5)
{
	// look in active list
	return activeList->Find(out, md5);
}


/***************************************************************/


/*                       Loading                               */



/***************************************************************/


/*
snd_err BufferManager::Load(WAVEFORMATEXTENSIBLE& _wfx, XAUDIO2_BUFFER& out, const char * path)
{
	// load first
	//initialize


	//loading
	DWORD fileType;
	BYTE * pDataBuffer = nullptr;
	WAVEFORMATEXTENSIBLE wfx = { 0 };
	XAUDIO2_BUFFER buffer = { 0 };

	// file is opened with given filename, generic defaults, handle is stored in hFile
	HANDLE _hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (_hFile == INVALID_HANDLE_VALUE) {
		return snd_err::ERR;
	}
	if (INVALID_SET_FILE_POINTER == SetFilePointer(_hFile, 0, NULL, FILE_BEGIN))
	{
		return snd_err::ERR;
	};

	/* INITIALIZATION --> MAKING A SINGLE VOICE 

	//buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	buffer.LoopCount = 0;

	DWORD dwChunkSize;
	DWORD dwChunkPosition;

	// find RIFF chunk and read in the filetype
	FindChunk(_hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	ReadChunkData(_hFile, &fileType, sizeof(DWORD), dwChunkPosition);


	// find FMT chunk and record it in waveformatextensible
	//if (filetype != fourccWAVE) return S_FALSE;
	FindChunk(_hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(_hFile, &wfx, dwChunkSize, dwChunkPosition);


	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(_hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(_hFile, pDataBuffer, dwChunkSize, dwChunkPosition);


	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

	out = buffer;
	_wfx = wfx; 

	VoiceManager::SubmitFactory(_wfx);

	CloseHandle(_hFile);

	return snd_err::OK;
}




HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{

	//start error code
	HRESULT hr = S_OK;

	// given a file pointer, returns the file to the start
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());


	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		switch (dwChunkType)
		{



			// FIND RIFF CHUNK
		case fourccRIFF:

			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;



			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;

		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;

	}

	return S_OK;
}

HRESULT ReadChunkData(HANDLE hFile, void * buf, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;

	// start from the top of the file and set the file pointer down by the given offset
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	// now that the file pointer is in the right place, write
	DWORD dwRead;
	if (0 == ReadFile(hFile, buf, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}
*/