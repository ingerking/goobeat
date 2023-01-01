#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "note.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class Resource{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	LPD3DXSPRITE BorderSprite;
	LPD3DXSPRITE BackgroundSprite;
	LPD3DXSPRITE TopImageSprite;
	LPD3DXSPRITE ReadyImageSprite;
	LPD3DXSPRITE GoImageSprite;
	LPDIRECT3DTEXTURE9 BorderTexture;
	LPDIRECT3DTEXTURE9 BackgroundTexture;
	LPDIRECT3DTEXTURE9 TopImageTexture;
	LPDIRECT3DTEXTURE9 ReadyImageTexture;
	LPDIRECT3DTEXTURE9 GoImageTexture;

	D3DXIMAGE_INFO BorderInfo;
	D3DXIMAGE_INFO BackgroundInfo;
	D3DXIMAGE_INFO TempInfo;

	D3DXVECTOR3* BorderVector;
	FLOAT width, height, exp;
	FLOAT btx, bty, brx, bry, bgox, bgoy;
public:
	Resource(const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, const FLOAT _Width, const FLOAT _Height, const FLOAT _Exp);
	~Resource();

	void Init();

	void DrawBorder();
	
	void DrawBackground();

	void DrawReady(int count);

	void DrawGO(int count);

	void DrawTOP();

	bool DrawReadyandGo(int count, Note* note);
};