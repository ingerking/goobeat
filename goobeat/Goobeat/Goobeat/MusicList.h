#pragma once

#include "Music.h"
#include <vector>
#include <algorithm>
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

using namespace std;

enum STATUS{STOP, MOVINGRIGHT, MOVINGLEFT};

class MusicList{
private:
	vector<Music*> musiclistvector[3];
	unsigned int location;
	unsigned int listsize;
	FLOAT exp;
	Music* current;
	FLOAT left, hspace, up, vspace;
	int fcr, fcg, fcb;
	
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPD3DXSPRITE FontSprite;
	ID3DXFont* Font;
	long fleft, fup, fright, fdown;

	STATUS status;
	int movecount;
	float volume;
public:
	MusicList(vector<Music*>* tempvector, const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, FLOAT _Exp, int _fcr, int _fcg, int _fcb, float volumef);
	~MusicList();
	bool MoveRight();
	bool MoveLeft();
	void DrawMusic(BOOL drawlist);
	void SelectMusic(int x, int y);
	Music* Selected();
	void DrawMusicInfo();
};