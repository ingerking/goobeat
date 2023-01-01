#pragma once

#include <stdlib.h>
#include <wchar.h>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <audiere.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "audiere.lib")

using namespace audiere;

class Music{
private:
	wchar_t* filename;
	wchar_t* musicfilepath;
	wchar_t* imagefilepath;
	bool wav;

	FILE* fp;

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	LPD3DXSPRITE MusicSprite;
	LPDIRECT3DTEXTURE9 MusicTexture;
	D3DXIMAGE_INFO MusicImageInfo;

	//A2dSound* sound;
	AudioDevicePtr	audiereDevice;
	OutputStreamPtr sound;


	FLOAT exp, mx, my;
	float volume;
public:
	Music(const wchar_t* fname, bool _wav);
	~Music();
	void InitMusic(const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, const FLOAT _Exp, const float volume);
	void PrintMusic(FLOAT x, FLOAT y);
	void Play();
	void Stop();
	wchar_t* GetFileName();
};