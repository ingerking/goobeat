#pragma once

#include <stdlib.h>
#include <wchar.h>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

class Button{
private:
	LPDIRECT3DDEVICE9 d3ddev;

	LPD3DXSPRITE ButtonSprite;
	LPDIRECT3DTEXTURE9 ButtonTexture;
	D3DXIMAGE_INFO ButtonImageInfo;

	FLOAT exp, mx, my;

	FLOAT left, up, hspace, vspace;
public:
	Button(const LPDIRECT3DDEVICE9 _d3ddev, const wchar_t* filename, FLOAT _Exp);
	~Button();
	void DrawButton(FLOAT x, FLOAT y);
};