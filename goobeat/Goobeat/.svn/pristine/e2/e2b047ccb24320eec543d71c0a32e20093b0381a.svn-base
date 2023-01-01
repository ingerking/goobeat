#pragma once

#include <stdlib.h>
#include <wchar.h>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <iostream>
#include <wchar.h>
#include "Music.h"
#include "Button.h"
#include "Num.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

using namespace std;

enum NoteStatus{NONE, INTRO, PERFECT, GOOD, GREAT, FAIL, FAST};
enum RankStatus{NON, F, C, B, A, S, SS, SSS, EX};

typedef struct NoteStruct{
	int notecount;
	NoteStatus status;
	int count;
}NoteStruct;

class Note{
private:
	Music* music;
	FILE* fp;
	int size;
	vector<bool> notevector[16];
	NoteStruct notestruct[16];
	int location;
	int combo;
	int maxcombo;
	float bonus;
	float perfectscore;
	float greatscore;
	float goodscore;
	float badscore;
	float score;
	float bonuscounter;
	float maxcombofloat;
	bool starthere[16];
	bool startflag;
	int fcr, fcg, fcb;

	RankStatus rankstatus;

	FLOAT exp;
	FLOAT left, up, hspace, vspace;

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	D3DXIMAGE_INFO NoteImageInfo;

	LPD3DXSPRITE NoteIntroSprite[25];
	LPDIRECT3DTEXTURE9 NoteIntroTexture[25];
	LPD3DXSPRITE NotePerfectSprite[11];
	LPDIRECT3DTEXTURE9 NotePerfectTexture[11];
	LPD3DXSPRITE NoteGoodSprite[11];
	LPDIRECT3DTEXTURE9 NoteGoodTexture[11];
	LPD3DXSPRITE NoteGreatSprite[11];
	LPDIRECT3DTEXTURE9 NoteGreatTexture[11];
	LPD3DXSPRITE NoteFailSprite[11];
	LPDIRECT3DTEXTURE9 NoteFailTexture[11];
	LPD3DXSPRITE NoteFastSprite[11];
	LPDIRECT3DTEXTURE9 NoteFastTexture[11];
	LPD3DXSPRITE ClearSprite;
	LPDIRECT3DTEXTURE9 ClearTexture;
	LPD3DXSPRITE FailedSprite;
	LPDIRECT3DTEXTURE9 FailedTexture;
	LPD3DXSPRITE FontSprite;
	ID3DXFont* Font;
	long fleft, fup, fright, fdown;

	FLOAT introx[25], perfectx[11], goodx[11], greatx[11], failx[11], fastx[11];
	FLOAT introy[25], perfecty[11], goody[11], greaty[11], faily[11], fasty[11];
	FLOAT clearx, cleary, failedx, failedy;

	Button* rankbutton;
	Button* startherebutton;
	Num* num[10];
public:
	Note(int _fcr, int _fcg, int _fcb);
	~Note();
	void InitNote(const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, const FLOAT _Exp);
	void CreateNote(Music* _music);
	void DeleteNote();
	void DrawNoteSprite(FLOAT x, FLOAT y, LPD3DXSPRITE Sprite, LPDIRECT3DTEXTURE9 Texture, FLOAT mx, FLOAT my);
	void DrawNote();
	bool NextNote(int* pcount);
	void keyinput(const int i);
	void PSound();
	void SSound();
	void Count();
	void CalcScore();
	void DrawResult();
	void PrintCombo();
	void DrawScore();
	bool CalCBonusScore();
	void CalcRank();
	void DrawClear();
	void DrawFailed();
	void DrawStarthere();
};