#include "MusicList.h"

MusicList::MusicList(vector<Music*>* tempvector, const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, FLOAT _Exp, int _fcr, int _fcg, int _fcb, float _volumef){
	fcr=_fcr;
	fcg=_fcg;
	fcb=_fcb;
	volume=0.5f;
	volume=_volumef;
	
	Font=NULL;
	FontSprite=NULL;
	
	d3d=_d3d;
	d3ddev=_d3ddev;


	exp=_Exp;
	movecount=0;
	status=STOP;

	vector<Music*>::iterator iter;
	Music* tempmusic;
	int count;
	for(count=0;count<3;count++){
		musiclistvector[count].resize((tempvector->size()+2)/3);
		musiclistvector[count].clear();
	}
	for(iter=tempvector->begin(), count=0;iter!=tempvector->end();iter++, count++){if(*iter==NULL){continue;}
		tempmusic=(Music*)(*iter);
		tempmusic->InitMusic(d3d, d3ddev, exp, volume);
		musiclistvector[count%3].push_back(tempmusic);
	}
	switch(count%3){
	case 0:
		break;
	case 1:
		musiclistvector[1].push_back(NULL);
		musiclistvector[2].push_back(NULL);
		break;
	case 2:
		musiclistvector[2].push_back(NULL);
		break;
	}
	location=0;
	listsize=musiclistvector[0].size();
	current=NULL;
	exp=_Exp;
	left=10.0f*exp;
	up=180.0f*exp;
	hspace=120.0f*exp;
	vspace=120.0f*exp;


	


	D3DXFONT_DESC fontDesc;	//폰트의 정보를 담을 구조체를 일단 정의한다.

	float fontheight=20.0f*exp;
	float fontwidth=10.0f*exp;

	ZeroMemory(&fontDesc, sizeof(fontDesc)); //폰트의 구조체를 초기화시킴
	fontDesc.Height = (int)fontheight; //폰트의 높이(대체로 너비의 2배쯤이 적당함)
	fontDesc.Width = (int)fontwidth; //폰트의 너비
	fontDesc.Weight = 1000; //폰트의 굵기 (0(얉음)~ 1000(굵음)의 값을 정함)
	fontDesc.Italic = false; //이탤릭?
	fontDesc.CharSet = DEFAULT_CHARSET; //디폴트로 선택하기
	wcscpy_s(fontDesc.FaceName, L"바탕"); // 글꼴 스타일


	D3DXCreateFontIndirect(d3ddev, &fontDesc, &Font); //폰트를 만든다.
	D3DXCreateSprite(d3ddev, &FontSprite);

	float boxleft=125.0f*exp, boxup=25.0f*exp, boxright=450.0f*exp, boxdown=85.0f*exp;
	
	fleft=(long)boxleft;
	fup=(long)boxup;
	fright=(long)boxright;
	fdown=(long)boxdown;

}

MusicList::~MusicList(){
	int i;
	Music* tempmusic;\
		vector<Music*>::iterator iter;
	for(i=0;i<3;i++){
		for(iter=musiclistvector[i].begin();iter!=musiclistvector[i].end();iter++){
			tempmusic=*iter;
			delete(tempmusic);
		}
	}
	if(Font!=NULL){Font->Release();}
	if(FontSprite!=NULL){FontSprite->Release();}
}

bool MusicList::MoveRight(){
	//int i, j;
	if(listsize>4&&location<listsize-4&&movecount==0){
		movecount=30;
		status=MOVINGRIGHT;
		return true;
	}
	else{
		return false;
	}
}


bool MusicList::MoveLeft(){
	if(location>0&&movecount==0){
		movecount=30;
		status=MOVINGLEFT;
		location--;
		return true;
	}
	else{
		return false;
	}
}
void MusicList::DrawMusic(BOOL drawlist){
	unsigned int i, j;
	if(drawlist){
		switch(status){
		case STOP:
			for(i=0;i<3;i++){
				for(j=0;j<4&&j<musiclistvector[i].size();j++){
					if(musiclistvector[i][j+location]==NULL){continue;}
					musiclistvector[i][j+location]->PrintMusic(FLOAT(left)+FLOAT(j)*hspace, FLOAT(up)+FLOAT(i)*vspace);
				}
			}
			break;
		case MOVINGRIGHT:
			if(movecount!=0){
				movecount--;
				for(i=0;i<3;i++){
					for(j=location;j<location+5&&j<musiclistvector[i].size();j++){
						if(musiclistvector[i][j]==NULL){continue;}
						musiclistvector[i][j]->PrintMusic(FLOAT(left)+FLOAT(j-1-location)*hspace+FLOAT(movecount)/30.0f*hspace, FLOAT(up+FLOAT(i)*vspace));
					}
				}
			}
			else{
				status=STOP;
				location++;
				for(i=0;i<3;i++){
					for(j=0;j<4&&j<musiclistvector[i].size();j++){
						if(musiclistvector[i][j+location]==NULL){continue;}
						musiclistvector[i][j+location]->PrintMusic(FLOAT(left)+FLOAT(j)*hspace, FLOAT(up)+FLOAT(i)*vspace);
					}
				}
			}
			break;
		case MOVINGLEFT:
			if(movecount!=0){
				movecount--;
				for(i=0;i<3;i++){
					for(j=location;j<location+5&&j<musiclistvector[i].size();j++){
						if(musiclistvector[i][j]==NULL){continue;}
						musiclistvector[i][j]->PrintMusic(FLOAT(left)+FLOAT(j-location)*hspace-FLOAT(movecount)/30.0f*hspace, FLOAT(up+FLOAT(i)*vspace));
					}
				}
			}
			else{
				status=STOP;
				for(i=0;i<3;i++){
					for(j=0;j<4&&j<musiclistvector[i].size();j++){
						if(musiclistvector[i][j+location]==NULL){continue;}
						musiclistvector[i][j+location]->PrintMusic(FLOAT(left)+FLOAT(j)*hspace, FLOAT(up)+FLOAT(i)*vspace);
					}
				}
			}
			break;
		}
	}
	if(current!=NULL){
		DrawMusicInfo();
		current->PrintMusic(left, left);
	}
}

void MusicList::SelectMusic(int x, int y){
	if(x+location>=musiclistvector[y].size()){return;}
	Music* temp=musiclistvector[y][x+location];
	if(temp==NULL){return;}
	else if(temp==current){return;}
	else{
		if(current!=NULL){current->Stop();}
		current=temp;
		current->Play();
	}
}

Music* MusicList::Selected(){
	if(current!=NULL){
		current->Stop();
	}
	return current;
}

void MusicList::DrawMusicInfo(){
	wchar_t* filename=current->GetFileName();
	RECT rc={fleft, fup, fright, fdown};
	FontSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Font->DrawTextW(FontSprite, filename, wcslen(filename), &rc, DT_LEFT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(fcr, fcg, fcb));
	FontSprite->End();
}