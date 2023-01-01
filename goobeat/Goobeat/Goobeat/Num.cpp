#include "Num.h"

Num::Num(const LPDIRECT3DDEVICE9 _d3ddev, const wchar_t* filename, FLOAT _Exp){
	D3DXIMAGE_INFO ImageInfo;

	NumSprite=NULL;
	NumTexture=NULL;
	d3ddev=NULL;
	
	d3ddev=_d3ddev;

	exp=_Exp;
	
	left=10.0f*exp;
	up=180.0f*exp;
	hspace=120.0f*exp;
	vspace=120.0f*exp;

	D3DXCreateSprite(d3ddev, &NumSprite);
	D3DXGetImageInfoFromFile(filename, &ImageInfo);
	D3DXCreateTextureFromFileEx(d3ddev, filename, ImageInfo.Width, ImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &NumTexture);

	
	

	mx=100.0f*exp/FLOAT(ImageInfo.Width);
	my=170.0f*exp/FLOAT(ImageInfo.Height);

	D3DXMATRIX NumZoom;

	D3DXMatrixTranslation(&NumZoom, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&NumZoom, mx, my, 0.0f);
	

	NumSprite->SetTransform(&NumZoom);
}

Num::~Num(){
		if(NumSprite!=NULL){NumSprite->Release();}
		if(NumTexture!=NULL){NumTexture->Release();}
}

void Num::DrawNum(FLOAT x, FLOAT y){
	D3DXVECTOR3 vector((left+x*hspace)/mx, (up+y*vspace)/my,0.0f);
	NumSprite->Begin(D3DXSPRITE_ALPHABLEND);
	NumSprite->Draw(NumTexture, NULL, NULL, &vector, 0xFFFFFFFF);
	NumSprite->End();
}