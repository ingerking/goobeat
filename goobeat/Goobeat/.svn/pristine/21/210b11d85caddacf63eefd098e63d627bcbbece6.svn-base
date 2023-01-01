#include "resource.h"

Resource::Resource(const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, const FLOAT _Width, const FLOAT _Height, const FLOAT _Exp){
	d3d=_d3d;
	d3ddev=_d3ddev;

	BorderSprite=NULL;
	BackgroundSprite=NULL;
	BorderTexture=NULL;
	BackgroundTexture=NULL;
	BorderVector=NULL;
	TopImageSprite=NULL;
	TopImageTexture=NULL;
	ReadyImageSprite=NULL;
	ReadyImageTexture=NULL;
	GoImageSprite=NULL;
	GoImageTexture=NULL;

	width=_Width;
	height=_Height;
	exp=_Exp;
}

Resource::~Resource(){
	if(BorderSprite!=NULL){BorderSprite->Release();}
	if(BackgroundSprite!=NULL){BackgroundSprite->Release();}
	if(BorderTexture!=NULL){BorderTexture->Release();}
	if(BackgroundTexture!=NULL){BackgroundTexture->Release();}
	if(BorderVector!=NULL){delete(BorderVector);}
	if(TopImageSprite!=NULL){TopImageSprite->Release();}
	if(TopImageTexture!=NULL){TopImageTexture->Release();}
	if(ReadyImageSprite!=NULL){ReadyImageSprite->Release();}
	if(ReadyImageTexture!=NULL){ReadyImageTexture->Release();}
	if(GoImageSprite!=NULL){GoImageSprite->Release();}
	if(GoImageTexture!=NULL){GoImageTexture->Release();}
}

void Resource::Init(){
	FLOAT bx, by, bgx, bgy;
	bx=0.0f;
	by=0.0f;
	bgx=0.0f;
	bgy=0.0f;
	btx=0.0f;
	bty=0.0f;
	brx=0.0f;
	bry=0.0f;
	bgox=0.0f;
	bgoy=0.0f;

	D3DXCreateTextureFromFileEx(d3ddev, L"..\\Resource\\Border.png", D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &BorderTexture);
	D3DXCreateTextureFromFileEx(d3ddev, L"..\\Resource\\Background.png", D3DX_DEFAULT, D3DX_DEFAULT, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &BackgroundTexture);
	D3DXGetImageInfoFromFile(L"..\\Resource\\Border.png", &BorderInfo);
	D3DXGetImageInfoFromFile(L"..\\Resource\\Background.png", &BackgroundInfo);

	D3DXCreateSprite(d3ddev, &BorderSprite);
	D3DXCreateSprite(d3ddev, &BackgroundSprite);


	bx=width*exp/FLOAT(BorderInfo.Width);
	by=((height-100.0f)*exp)/FLOAT(BorderInfo.Height);
	bgx=width*exp/FLOAT(BackgroundInfo.Width);
	bgy=((height-100.0f)*exp)/FLOAT(BackgroundInfo.Height);
	
	BorderVector=new D3DXVECTOR3(0.0f, 160.0f, 0.0f);

	D3DXMATRIX BorderZoom;
	D3DXMATRIX BackgroundZoom;

	D3DXMatrixTranslation(&BorderZoom, 0, 0, 0);
	D3DXMatrixTranslation(&BackgroundZoom, 0, 0, 0);

	D3DXMatrixScaling(&BorderZoom, bx, by, 0.0f);
	D3DXMatrixScaling(&BackgroundZoom, bgx, bgy, 0.0f);
	BorderSprite->SetTransform(&BorderZoom);
	BackgroundSprite->SetTransform(&BackgroundZoom);
	
	
	D3DXGetImageInfoFromFile(L"..\\Resource\\top.png", &TempInfo);
	D3DXCreateTextureFromFileEx(d3ddev, L"..\\Resource\\top.png", TempInfo.Width, TempInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &TopImageTexture);
	
	D3DXCreateSprite(d3ddev, &TopImageSprite);
	
	btx=width*exp/FLOAT(TempInfo.Width);
	bty=160.0f*exp/FLOAT(TempInfo.Height);
	
	D3DXMATRIX TopImageZoom;
	D3DXMatrixTranslation(&TopImageZoom, 0, 0, 0);

	D3DXMatrixScaling(&TopImageZoom, btx, bty, 0.0f);
	
	TopImageSprite->SetTransform(&TopImageZoom);

	
	
	D3DXGetImageInfoFromFile(L"..\\Resource\\ready.png", &TempInfo);
	D3DXCreateTextureFromFileEx(d3ddev, L"..\\Resource\\ready.png", TempInfo.Width, TempInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &ReadyImageTexture);
	
	D3DXCreateSprite(d3ddev, &ReadyImageSprite);
	
	brx=400.0f*exp/FLOAT(TempInfo.Width);
	bry=150.0f*exp/FLOAT(TempInfo.Height);
	
	D3DXMATRIX ReadyImageZoom;
	D3DXMatrixTranslation(&ReadyImageZoom, 0.0f, 0.0f, 0.0f);

	D3DXMatrixScaling(&ReadyImageZoom, brx, bry, 0.0f);
	
	ReadyImageSprite->SetTransform(&ReadyImageZoom);
	
	D3DXCreateSprite(d3ddev, &GoImageSprite);
	D3DXGetImageInfoFromFile(L"..\\Resource\\go.png", &TempInfo);
	D3DXCreateTextureFromFileEx(d3ddev, L"..\\Resource\\go.png", TempInfo.Width, TempInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &GoImageTexture);
	
	
	bgox=300.0f*exp/FLOAT(TempInfo.Width);
	bgoy=200.0f*exp/FLOAT(TempInfo.Height);
	
	D3DXMATRIX GoImageZoom;
	D3DXMatrixTranslation(&GoImageZoom, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&GoImageZoom, bgox, bgoy, 0.0f);
	
	GoImageSprite->SetTransform(&GoImageZoom);
}

void Resource::DrawBorder(){
	BorderSprite->Begin(D3DXSPRITE_ALPHABLEND);
	BorderSprite->Draw(BorderTexture, NULL, NULL, BorderVector, 0xFFFFFFFF);
	BorderSprite->End();
}
	
void Resource::DrawBackground(){
	BackgroundSprite->Begin(D3DXSPRITE_ALPHABLEND);
	BackgroundSprite->Draw(BackgroundTexture, NULL, NULL, BorderVector, 0xFFFFFFFF);
	BackgroundSprite->End();
}

void Resource::DrawReady(int count){
	D3DCOLOR tempcolor=0x08080808*count;
	tempcolor+=0x0F0F0F0F;

	D3DXVECTOR3 tempvector(40.0f/brx*exp, 340.0f/bry*exp, 0.0f);
	
	ReadyImageSprite->Begin(D3DXSPRITE_ALPHABLEND);
	ReadyImageSprite->Draw(ReadyImageTexture, NULL, NULL, &tempvector, tempcolor);
	ReadyImageSprite->End();
}

void Resource::DrawGO(int count){
	D3DCOLOR tempcolor=0x08080808*count;
	tempcolor+=0x0F0F0F0F;

	D3DXVECTOR3 tempvector(90.0f/bgox*exp, 320.0f/bgoy*exp, 0.0f);
	
	GoImageSprite->Begin(D3DXSPRITE_ALPHABLEND);
	GoImageSprite->Draw(GoImageTexture, NULL, NULL, &tempvector, tempcolor);
	GoImageSprite->End();

}

void Resource::DrawTOP(){
	TopImageSprite->Begin(D3DXSPRITE_ALPHABLEND);
	TopImageSprite->Draw(TopImageTexture, NULL, NULL, NULL, 0xFFFFFFFF);
	TopImageSprite->End();
}

bool Resource::DrawReadyandGo(int count, Note* note){
	if(count==0){
			note->DrawStarthere();
			return true;
	}
	else{
		if(count<=360&&count>330){
			DrawReady(360-count);
		}
		else if(count>270){
			DrawReady(30);
		}
		else if(count>240){
			DrawReady(count-240);
		}
		else if(count>210){
			;
		}
		else if(count>180){
			DrawGO(210-count);
		}
		else if(count>60){
			DrawGO(30);
		}
		else if(count>0){
			note->DrawStarthere();
		}

		return false;
	}
}