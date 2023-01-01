#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "resource.h"
#include "MusicList.h"
#include "Button.h"
#include "note.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


enum Status{SELECTING, READY, STANDBY, PLAYING, RESULT};


class UI{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	MusicList* musiclist;
	Resource* resource;

	Button* prevbutton, *nextbutton, *startbutton;
	Button* buttonon;
	Note* note;

	FLOAT width, height, exp;

	Status status;
	int canmove;

	int key[16];
	int keylock;
	int fcr, fcg, fcb;

	int count;
	int count2;
	bool started;
	bool endflag;
	bool iskeypressedbool[16];
public:
	UI(const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, const FLOAT _Width, const FLOAT _Height, const FLOAT _Exp, int _fcr, int _fcg, int _fcb, int* pkey);
	~UI();
	void Init();
	void AddMusicList(MusicList* _musiclist);
	bool iskeypressed(int i);
	bool iskeypressedlong(int i);
	void KeyInput();
	void Draw();
	void SleepFrame(int k);
	FLOAT CalcFPS() ;
};