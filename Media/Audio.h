#ifndef _AUDIO_H
#define _AUDIO_H

#include <stdint.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/sysmem.h>

#include "FileBuffer.h"

typedef struct
{
	SceUID			soundThread;
	SceUID			readThread;
	SceUID			fileHandle;
	uint8_t*		header;
	uint8_t*		buffer;
	uint8_t*		readBuf;
	uint8_t*		fillBuf;
	uint32_t		dataSize;
	uint32_t		offset;
	uint32_t		readEnd;
	uint32_t		endflag;
	uint32_t		memory;
	uint32_t		format;
	FileBuffer*		fileBuffer;
	void*			handle;
	uint32_t		mode;
	uint32_t		channels;
	uint32_t		samplingRate;
	int16_t			wavBuff[BUFNUM][USER_GRAIN*STEREO];

} AudioHandler;

int32_t InitializeAudio(AudioHandler* audioHandler);
int32_t TerminateAudio(AudioHandler* audioHandler);

int32_t LoadWav(AudioHandler* audioHandler, char* filename, SceUInt32 mode, SceUInt32 memory);
int32_t LoadOgg(AudioHandler* audioHandler, char* filename, SceUInt32 mode, SceUInt32 memory);

int32_t TestOgg(AudioHandler* audioHandler);

int32_t PlayAudio(AudioHandler* audioHandler);
int32_t StopAudio(AudioHandler* audioHandler);

int32_t GetAudioStatus(AudioHandler* audioHandler);

#endif // _AUDIO_H
