#include "Button.h"

Button::Button(const LPDIRECT3DDEVICE9 _d3ddev, const wchar_t* filename, FLOAT _Exp){
	ButtonSprite=NULL;
	ButtonTexture=NULL;
	d3ddev=NULL;
	
	d3ddev=_d3ddev;

	exp=_Exp;
	
	left=10.0f*exp;
	up=180.0f*exp;
	hspace=120.0f*exp;
	vspace=120.0f*exp;

	D3DXCreateSprite(d3ddev, &ButtonSprite);
	D3DXGetImageInfoFromFile(filename, &ButtonImageInfo);
	D3DXCreateTextureFromFileEx(d3ddev, filename, ButtonImageInfo.Width, ButtonImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &ButtonTexture);

	
	

	mx=100.0f*exp/FLOAT(ButtonImageInfo.Width);
	my=100.0f*exp/FLOAT(ButtonImageInfo.Height);

	D3DXMATRIX ButtonZoom;

	D3DXMatrixTranslation(&ButtonZoom, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&ButtonZoom, mx, my, 0.0f);
	

	ButtonSprite->SetTransform(&ButtonZoom);
}

Button::~Button(){
		if(ButtonSprite!=NULL){ButtonSprite->Release();}
		if(ButtonTexture!=NULL){ButtonTexture->Release();}
}

void Button::DrawButton(FLOAT x, FLOAT y){
	D3DXVECTOR3 vector((left+x*hspace)/mx, (up+y*vspace)/my,0.0f);
	ButtonSprite->Begin(D3DXSPRITE_ALPHABLEND);
	ButtonSprite->Draw(ButtonTexture, NULL, NULL, &vector, 0xFFFFFFFF);
	ButtonSprite->End();
}