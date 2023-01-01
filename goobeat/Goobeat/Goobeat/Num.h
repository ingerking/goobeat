#pragma once

#include <stdlib.h>
#include <wchar.h>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class Num{
private:
	LPDIRECT3DDEVICE9 d3ddev;

	LPD3DXSPRITE NumSprite;
	LPDIRECT3DTEXTURE9 NumTexture;

	FLOAT exp, mx, my;

	FLOAT left, up, hspace, vspace;
public:
	Num(const LPDIRECT3DDEVICE9 _d3ddev, const wchar_t* filename, FLOAT _Exp);
	~Num();
	void DrawNum(FLOAT x, FLOAT y);
};