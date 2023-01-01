#include "UI.h"




UI::UI(const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, const FLOAT _Width, const FLOAT _Height, const FLOAT _Exp, int _fcr, int _fcg, int _fcb, int* pkey){
	for(int a=0;a<16;a++){
		key[a]=pkey[a];
	}

	keylock=0;
	count=0;
	started=false;
	endflag=false;

	fcr=_fcr;
	fcg=_fcg;
	fcb=_fcb;
	resource=NULL;
	d3d=_d3d;
	d3ddev=_d3ddev;
	musiclist=NULL;
	width=_Width;
	height=_Height;
	exp=_Exp;
	canmove=0;
	status=SELECTING;
	prevbutton=NULL;
	nextbutton=NULL;
	startbutton=NULL;
	buttonon=NULL;
	note=NULL;
	for(int i=0;i<16;i++){
		iskeypressedbool[i]=false;
	}
	Init();
}

UI::~UI(){
	if(resource!=NULL){delete resource;}
	if(prevbutton!=NULL){delete prevbutton;}
	if(nextbutton!=NULL){delete nextbutton;}
	if(startbutton!=NULL){delete startbutton;}
	if(note!=NULL){delete note;}
	if(buttonon!=NULL){delete buttonon;}
}


void UI::Init(){
	resource=new Resource(d3d, d3ddev, width, height, exp);
	resource->Init();
	prevbutton=new Button(d3ddev, L"..\\Resource\\prevbutton.png", exp);
	nextbutton=new Button(d3ddev, L"..\\Resource\\nextbutton.png", exp);
	startbutton=new Button(d3ddev, L"..\\Resource\\startbutton.png", exp);
	buttonon=new Button(d3ddev, L"..\\Resource\\button_on.png", exp);
	note=new Note(fcr, fcg, fcb);
	note->InitNote(d3d, d3ddev, exp);
}

void UI::AddMusicList(MusicList* _musiclist){
	musiclist=_musiclist;
}

bool UI::iskeypressed(int i){
	if((GetAsyncKeyState(key[i]) & 0x8001) == 0x8001) {
		return true;
	}
	else{
		return false;
	}
}

bool UI::iskeypressedlong(int i){
	if(GetAsyncKeyState(key[i]) & 0x8000) {
		return true;
	}
	else{
		return false;
	}
}

void UI::KeyInput(){
	int i;
	if(keylock==0){
		switch(status){
		case SELECTING:
			for(i=0;i<12;i++){
				if(iskeypressed(i)){
					musiclist->SelectMusic(i%4, i/4);
				}
			}
			if(iskeypressed(15)){
				Music* temp=musiclist->Selected();
				if(temp!=NULL){
					note->CreateNote(temp);
					count2=0;
					keylock=360;
					status=READY;
				}
			}
			else if(iskeypressed(12)){
				if(musiclist->MoveLeft()){
					keylock=30;
				}
			}
			else if(iskeypressed(13)){
				if(musiclist->MoveRight()){
					keylock=30;
				}
			}
			break;
		case READY:
		case STANDBY:
			break;
		case PLAYING:
			for(i=0;i<16;i++){
				if(iskeypressed(i)){
					note->keyinput(i);
				}
			}
			break;
		case RESULT:
			if(endflag){
				if(iskeypressed(15)){

					note->DeleteNote();
					status=SELECTING;
					endflag=false;
					started=false;
				}
			}
			break;
		}
	}

	for(i=0;i<16;i++){
		if(iskeypressedlong(i)){
			iskeypressedbool[i]=true;
		}
	}

	if((GetAsyncKeyState(VK_ESCAPE) & 0x8001) == 0x8001) {
		if(status==READY){
			status=SELECTING;
			count2=0;
			note->DeleteNote();
			endflag=false;
			started=false;
			keylock=0;

		}
		else if(status==STANDBY){

			status=SELECTING;
			count2=0;
			note->DeleteNote();
			endflag=false;
			started=false;
			keylock=0;
		}
		else if(status==PLAYING){

			note->SSound();
			status=SELECTING;
			count2=0;
			note->DeleteNote();
			endflag=false;
			started=false;
			keylock=0;
		}
	}
}

void UI::Draw(){
	static float countleft=0.0f;
	float k=CalcFPS();
	float tempcount=0.0f;
	int count3=0;
	int i=0;

	if(k<6.0f){
		tempcount=6.0f/k;
		count3=int(tempcount);
		countleft+=tempcount-(float)count3;
		while(countleft>=1.0f){
			countleft-=1.0f;
			count3+=1;
		}
	}
	else{
		count3=1;
	}



	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	KeyInput();

	resource->DrawBackground();
	resource->DrawTOP();
	switch(status){
	case SELECTING:
		musiclist->DrawMusic(true);
		prevbutton->DrawButton(0.0f, 3.0f);
		nextbutton->DrawButton(1.0f, 3.0f);
		startbutton->DrawButton(3.0f, 3.0f);
		break;
	case READY:
		musiclist->DrawMusic(false);
		if(resource->DrawReadyandGo(keylock, note)){
			status=STANDBY;
		}
		break;
	case STANDBY:
		musiclist->DrawMusic(false);
		note->DrawStarthere();
		count3=1;
		countleft=0.0f;
		status=PLAYING;
		break;
	case PLAYING:
		musiclist->DrawMusic(false);
		for(i=0;i<count3;i++){
			note->DrawStarthere();
			if(note->NextNote(&count)){
				status=RESULT;
				note->SSound();
				count2=0;
			}
			if(count2>60){
				if(!started){
					started=true;
					note->PSound();
				}
			}
			else{
				count2++;
			}
		}
		note->CalcScore();
		note->DrawScore();
		note->PrintCombo();
		note->DrawNote();
		break;
	case RESULT:
		musiclist->DrawMusic(false);
		note->DrawScore();
		if(!endflag){
			endflag=note->CalCBonusScore();
		}
		else{
			note->CalcRank();
			note->DrawResult();
			prevbutton->DrawButton(3.0f, 3.0f);
		}
		break;
	}

	if(keylock!=0){keylock--;}

	resource->DrawBorder();

	for(i=0;i<16;i++){
		if(iskeypressedbool[i]){
			buttonon->DrawButton(float(i%4),float(i/4));
			iskeypressedbool[i]=false;
		}
	}



	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}

void UI::SleepFrame(int k){
	int i;
	for(i=0;i<k;i++){
		CalcFPS();
	}
}


FLOAT UI::CalcFPS() {
	static int cnt = 0;
	static DWORD curr_time = 0, prev_time = 0, elapsed = 0;
	static float fps = 0.0f;

	prev_time = curr_time;
	curr_time = timeGetTime();
	cnt++;
	elapsed += curr_time - prev_time;

	if(elapsed >= 100) {
		fps = cnt * 100.0f / elapsed;
		elapsed = 0;
		cnt = 0;
	}
	return fps;
}
