#include "Music.h"

Music::Music(const wchar_t* fname, bool _wav){
	filename=NULL;
	musicfilepath=NULL;
	imagefilepath=NULL;
	volume=0.5f;
	sound=NULL;
	
	wav=_wav;

	filename=(wchar_t*)malloc(sizeof(wchar_t)*(wcslen(fname)+1));
	swprintf_s(filename, wcslen(fname)+1, L"%s", fname);


	if(filename!=NULL){
		musicfilepath=(wchar_t*)malloc(sizeof(wchar_t)*(wcslen(L"..\\Music\\")+wcslen(filename)+1));
		swprintf_s(musicfilepath, wcslen(L"..\\Music\\")+wcslen(filename)+1, L"..\\Music\\%s", filename);

		imagefilepath=(wchar_t*)malloc(sizeof(wchar_t)*(wcslen(L"..\\Image\\.png")+wcslen(filename)+1));
		swprintf_s(imagefilepath, wcslen(L"..\\Image\\.png")+wcslen(filename)+1, L"..\\Image\\%s.png", filename);
	}

	d3d=NULL;
	d3ddev=NULL;
	audiereDevice=NULL;
	sound=NULL;
	fp=NULL;

	MusicSprite=NULL;
	MusicTexture=NULL;
}

Music::~Music(){
	if(sound!=NULL){sound->stop();}
	if(filename!=NULL){free(filename);}
	if(musicfilepath!=NULL){free(musicfilepath);}
	if(imagefilepath!=NULL){free(imagefilepath);}
	if(MusicSprite!=NULL){MusicSprite->Release();}
	if(MusicTexture!=NULL){MusicTexture->Release();}
}

void Music::InitMusic(const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, const FLOAT _Exp, float _volume){
	d3d=_d3d;
	d3ddev=_d3ddev;

	exp=_Exp;
	volume=_volume;
	
	audiereDevice=OpenDevice();

	std::string str;
		int nLen = ::WideCharToMultiByte(CP_ACP, 0, musicfilepath, -1, NULL, 0, NULL, NULL);
		str.clear();
		str.resize(nLen, 0);
		::WideCharToMultiByte(CP_ACP, 0, musicfilepath, -1, &str[0], nLen, NULL, NULL);

	sound=OpenSound(audiereDevice, str.c_str(), false);
	
	FILE* fp;
	_wfopen_s(&fp, imagefilepath, L"r");
	if(fp==NULL){
		D3DXCreateSprite(d3ddev, &MusicSprite);
		D3DXGetImageInfoFromFile(L"..\\Resource\\noimage.png", &MusicImageInfo);
		D3DXCreateTextureFromFileEx(d3ddev, L"..\\Resource\\noimage.png", MusicImageInfo.Width,MusicImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &MusicTexture);
	}
	else{
		fclose(fp);
		D3DXCreateSprite(d3ddev, &MusicSprite);
		D3DXGetImageInfoFromFile(imagefilepath, &MusicImageInfo);
		D3DXCreateTextureFromFileEx(d3ddev, imagefilepath, MusicImageInfo.Width,MusicImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &MusicTexture);
	}

	

	mx=100.0f*exp/FLOAT(MusicImageInfo.Width);
	my=100.0f*exp/FLOAT(MusicImageInfo.Height);

	D3DXMATRIX MusicZoom;

	D3DXMatrixTranslation(&MusicZoom, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&MusicZoom, mx, my, 0.0f);
	

	MusicSprite->SetTransform(&MusicZoom);


}

void Music::PrintMusic(FLOAT x, FLOAT y){
	D3DXVECTOR3 vector(x/mx, y/my,0.0f);
	MusicSprite->Begin(D3DXSPRITE_ALPHABLEND);
	MusicSprite->Draw(MusicTexture, NULL, NULL, &vector, 0xFFFFFFFF);
	MusicSprite->End();
}

void Music::Play(){
	sound->setVolume(volume);
	sound->setRepeat(false);
	sound->play();
}

void Music::Stop(){
	sound->stop();
	sound->reset();
}

wchar_t* Music::GetFileName(){
	return filename;
}
