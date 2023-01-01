#pragma once

#include <windows.h>
#include <assert.h>
#include<fstream>
#include<vector>
using namespace std;


struct CHUNK {
    DWORD   id;
    DWORD   size;

    BYTE    buff[4];
};

struct RIFF {
    DWORD   ID;             // RIFF(0x46464952 small-endian form) 
    DWORD   Size;           // chunk의 나머지 크기 

    DWORD   Format;         // WAVE(0x45564157 small-endian form) 
};

struct FORMAT {
    DWORD   ID;             // fmt (0x20746D66 small_endian form) 
    DWORD   Size;           //  

    WORD    AudioFormat;    // 오디오 형식: PCM = 1  
    WORD    NumChannels;    // 채널수(mono:1,stereo:2) 
    DWORD   SamplesPerSec;  // 초당샘플수(8000,11025,2205,44100) 
    DWORD   BytesPerSec;    // 초당바이트수=초당샘플수*채널수*샘플당비트수/8 
    WORD    BlockAlign;     // 샘플당바이트수=채널수*샘플당비트수/8 
    WORD    BitsPerSample;  // 샘플당비트수(8bits:8,16bits:16) 
};

struct FACT {
    DWORD   ID;             // fact (0x74636166) 
    DWORD   Size;

    DWORD   dwSampleLength; // 샘플 길이 
};

struct DATA {
    DWORD   ID;             // data (0x61747174) 
    DWORD   Size;           // 샘플 길이 * 채널수 

    //BYTE    Buff[4];
	short	Data[1];
};

struct WAVE {
    RIFF    *riff;
    FORMAT  *format;
    FACT    *fact;
    DATA    *data;
};

void print_wave_info(WAVE *wave);

CHUNK *read_chunk(FILE *fptr);

WAVE *read_wave(const char *fname);

void free_wave(WAVE *wave);