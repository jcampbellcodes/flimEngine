#include "ThreadLoadWaveCommand.h"
#include "VoiceManager.h"
#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void * buf, DWORD buffersize, DWORD bufferoffset);
snd_err LoadWaveAndSet(BufferNode*& out, const char * path, void(*cb)(void));

void ThreadLoadWaveCommand::execute()
{
	LoadWaveAndSet(cmd.bufferNode, cmd.wavePath.c_str(), cmd.loadedCallback);

}





snd_err LoadWaveAndSet(BufferNode*& out, const char * path, void(*cb)(void))
{
	// load first
	//initialize


	//loading
	DWORD fileType;
	BYTE * pDataBuffer = nullptr;
	WAVEFORMATEXTENSIBLE* wfx = new WAVEFORMATEXTENSIBLE();
	XAUDIO2_BUFFER* buffer = new XAUDIO2_BUFFER();

	// file is opened with given filename, generic defaults, handle is stored in hFile
	HANDLE _hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (_hFile == INVALID_HANDLE_VALUE) {
		return snd_err::ERR;
	}
	if (INVALID_SET_FILE_POINTER == SetFilePointer(_hFile, 0, NULL, FILE_BEGIN))
	{
		return snd_err::ERR;
	};

	/* INITIALIZATION --> MAKING A SINGLE VOICE */

	//buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	buffer->LoopCount = 0;

	DWORD dwChunkSize;
	DWORD dwChunkPosition;

	// find RIFF chunk and read in the filetype
	FindChunk(_hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	ReadChunkData(_hFile, &fileType, sizeof(DWORD), dwChunkPosition);


	// find FMT chunk and record it in waveformatextensible
	//if (filetype != fourccWAVE) return S_FALSE;
	FindChunk(_hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(_hFile, wfx, dwChunkSize, dwChunkPosition);


	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(_hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(_hFile, pDataBuffer, dwChunkSize, dwChunkPosition);


	buffer->AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer->pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer->Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer



	out->InitializeData(buffer, wfx);

	if (cb)
	{
		cb();
	}

	WAVEFORMATEXTENSIBLE _wfx = *wfx;

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