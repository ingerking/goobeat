#include "Note.h"



Note::Note(int _fcr, int _fcg, int _fcb){
	fcr=_fcr;
	fcg=_fcg;
	fcb=_fcb;
	failedx=0.0f;
	failedy=0.0f;
	clearx=0.0f;
	cleary=0.0f;
	int i=0;
	fp=NULL;
	for(i=0;i<16;i++){
		notevector[i].resize(0);
		notevector[i].clear();
		notestruct[i].notecount=0;
		notestruct[i].count=0;
		notestruct[i].status=NONE;
		starthere[i]=false;
	}
	for(i=0;i<10;i++){
		num[i]=NULL;
	}
	startflag=false;
	size=0;
	location=0;
	music=NULL;
	exp=0.0f;
	left=0.0f;
	up=0.0f;
	hspace=0.0f;
	vspace=0.0f;

	d3d=NULL;
	d3ddev=NULL;
	FontSprite=NULL;
	Font=NULL;
	ClearSprite=NULL;
	ClearTexture=NULL;
	FailedSprite=NULL;
	FailedTexture=NULL;

	for(i=0;i<25;i++){
		NoteIntroSprite[i]=NULL;
		NoteIntroTexture[i]=NULL;
	}
	for(i=0;i<11;i++){
		NotePerfectSprite[i]=NULL;
		NotePerfectTexture[i]=NULL;
		NoteGoodSprite[i]=NULL;
		NoteGoodTexture[i]=NULL;
		NoteGreatSprite[i]=NULL;
		NoteGreatTexture[i]=NULL;
		NoteFailSprite[i]=NULL;
		NoteFailTexture[i]=NULL;
		NoteFastSprite[i]=NULL;
		NoteFastTexture[i]=NULL;
	}
	rankbutton=NULL;
	startherebutton=NULL;
}

Note::~Note(){
	int i=0;

	for(i=0;i<25;i++){
		if(NoteIntroSprite[i]==NULL){NoteIntroSprite[i]->Release();}
		if(NoteIntroTexture[i]==NULL){NoteIntroSprite[i]->Release();}
	}
	for(i=0;i<11;i++){
		if(NotePerfectSprite[i]==NULL){NotePerfectSprite[i]->Release();}
		if(NotePerfectTexture[i]==NULL){NotePerfectSprite[i]->Release();}
		if(NoteGoodSprite[i]==NULL){NoteGoodSprite[i]->Release();}
		if(NoteGoodTexture[i]==NULL){NoteGoodSprite[i]->Release();}
		if(NoteGreatSprite[i]==NULL){NoteGreatSprite[i]->Release();}
		if(NoteGreatTexture[i]==NULL){NoteGreatSprite[i]->Release();}
		if(NoteFailSprite[i]==NULL){NoteFailSprite[i]->Release();}
		if(NoteFailTexture[i]==NULL){NoteFailSprite[i]->Release();}
		if(NoteFastSprite[i]==NULL){NoteFastSprite[i]->Release();}
		if(NoteFastTexture[i]==NULL){NoteFastSprite[i]->Release();}
	}
	for(i=0;i<10;i++){
		if(num[i]!=NULL){delete num[i];}
	}

	if(FontSprite!=NULL){FontSprite->Release();}
	if(Font!=NULL){Font->Release();}
	if(rankbutton!=NULL){
		delete rankbutton;
		rankbutton=NULL;
	}
	if(ClearSprite!=NULL){ClearSprite->Release();}
	if(ClearTexture!=NULL){ClearTexture->Release();}
	if(FailedSprite!=NULL){FailedSprite->Release();}
	if(FailedTexture!=NULL){FailedTexture->Release();}
	if(startherebutton!=NULL){delete startherebutton;}
	DeleteNote();
}

void Note::InitNote(const LPDIRECT3D9 _d3d, const LPDIRECT3DDEVICE9 _d3ddev, const FLOAT _Exp){
	int i=0;
	FILE* fp=NULL;

	wchar_t* introfilepath, *perfectfilepath, *goodfilepath, *greatfilepath, *failfilepath, *fastfilepath, *numpath;
	int introlength, perfectlength, goodlength, greatlength, faillength, fastlength, numlength;
	introlength=wcslen(L"..\\Resource\\Intro\\00.png")+1;
	perfectlength=wcslen(L"..\\Resource\\Perfect\\00.png")+1;
	goodlength=wcslen(L"..\\Resource\\Good\\00.png")+1;
	greatlength=wcslen(L"..\\Resource\\Great\\00.png")+1;
	faillength=wcslen(L"..\\Resource\\Fail\\00.png")+1;
	fastlength=wcslen(L"..\\Resource\\Fast\\00.png")+1;
	numlength=wcslen(L"..\\Resource\\num_0.png")+1;


	introfilepath=(wchar_t*)malloc(sizeof(wchar_t*)*introlength);
	perfectfilepath=(wchar_t*)malloc(sizeof(wchar_t*)*perfectlength);
	goodfilepath=(wchar_t*)malloc(sizeof(wchar_t*)*goodlength);
	greatfilepath=(wchar_t*)malloc(sizeof(wchar_t*)*greatlength);
	failfilepath=(wchar_t*)malloc(sizeof(wchar_t*)*faillength);
	fastfilepath=(wchar_t*)malloc(sizeof(wchar_t*)*fastlength);
	numpath=(wchar_t*)malloc(sizeof(wchar_t*)*numlength);

	d3d=_d3d;
	d3ddev=_d3ddev;

	exp=_Exp;

	left=10.0f*exp;
	up=180.0f*exp;
	hspace=120.0f*exp;
	vspace=120.0f*exp;

	D3DXFONT_DESC fontDesc;	//폰트의 정보를 담을 구조체를 일단 정의한다.

	float fontheight=40.0f*exp;
	float fontwidth=20.0f*exp;

	ZeroMemory(&fontDesc, sizeof(fontDesc)); //폰트의 구조체를 초기화시킴
	fontDesc.Height = (int)fontheight; //폰트의 높이(대체로 너비의 2배쯤이 적당함)
	fontDesc.Width = (int)fontwidth; //폰트의 너비
	fontDesc.Weight = 1000; //폰트의 굵기 (0(얉음)~ 1000(굵음)의 값을 정함)
	fontDesc.Italic = false; //이탤릭?
	fontDesc.CharSet = DEFAULT_CHARSET; //디폴트로 선택하기
	wcscpy_s(fontDesc.FaceName, L"바탕"); // 글꼴 스타일


	D3DXCreateFontIndirect(d3ddev, &fontDesc, &Font); //폰트를 만든다.
	D3DXCreateSprite(d3ddev, &FontSprite);

	float boxleft=0.0f*exp, boxup=100.0f*exp, boxright=450.0f*exp, boxdown=160.0f*exp;
	
	fleft=(long)boxleft;
	fup=(long)boxup;
	fright=(long)boxright;
	fdown=(long)boxdown;

	for(i=0;i<25;i++){
		swprintf_s(introfilepath, introlength, L"..\\Resource\\Intro\\%02d.png", i);

		_wfopen_s(&fp, introfilepath, L"r");
		if(fp!=NULL){

			D3DXCreateSprite(d3ddev, &NoteIntroSprite[i]);
			D3DXGetImageInfoFromFile(introfilepath, &NoteImageInfo);
			D3DXCreateTextureFromFileEx(d3ddev, introfilepath, NoteImageInfo.Width, NoteImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &NoteIntroTexture[i]);

			introx[i]=100.0f*exp/FLOAT(NoteImageInfo.Width);
			introy[i]=100.0f*exp/FLOAT(NoteImageInfo.Height);
			D3DXMATRIX Zoom;

			D3DXMatrixTranslation(&Zoom, 0.0f, 0.0f, 0.0f);
			D3DXMatrixScaling(&Zoom, introx[i], introy[i], 0.0f);

			NoteIntroSprite[i]->SetTransform(&Zoom);
			fclose(fp);
			fp=NULL;
		}
	}
	for(i=0;i<11;i++){
		swprintf(perfectfilepath, perfectlength, L"..\\Resource\\Perfect\\%02d.png", i);
		_wfopen_s(&fp, perfectfilepath, L"r");
		if(fp!=NULL){

			D3DXCreateSprite(d3ddev, &NotePerfectSprite[i]);
			D3DXGetImageInfoFromFile(perfectfilepath, &NoteImageInfo);
			D3DXCreateTextureFromFileEx(d3ddev, perfectfilepath, NoteImageInfo.Width, NoteImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &NotePerfectTexture[i]);

			perfectx[i]=100.0f*exp/FLOAT(NoteImageInfo.Width);
			perfecty[i]=100.0f*exp/FLOAT(NoteImageInfo.Height);
			D3DXMATRIX PerfectZoom;

			D3DXMatrixTranslation(&PerfectZoom, 0.0f, 0.0f, 0.0f);
			D3DXMatrixScaling(&PerfectZoom, perfectx[i], perfecty[i], 0.0f);

			NotePerfectSprite[i]->SetTransform(&PerfectZoom);
			fclose(fp);
			fp=NULL;
		}
		swprintf(goodfilepath, goodlength, L"..\\Resource\\Good\\%02d.png", i);

		_wfopen_s(&fp, goodfilepath, L"r");
		if(fp!=NULL){

			D3DXCreateSprite(d3ddev, &NoteGoodSprite[i]);
			D3DXGetImageInfoFromFile(goodfilepath, &NoteImageInfo);
			D3DXCreateTextureFromFileEx(d3ddev, goodfilepath, NoteImageInfo.Width, NoteImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &NoteGoodTexture[i]);

			goodx[i]=100.0f*exp/FLOAT(NoteImageInfo.Width);
			goody[i]=100.0f*exp/FLOAT(NoteImageInfo.Height);
			D3DXMATRIX GoodZoom;

			D3DXMatrixTranslation(&GoodZoom, 0.0f, 0.0f, 0.0f);
			D3DXMatrixScaling(&GoodZoom, goodx[i], goody[i], 0.0f);

			NoteGoodSprite[i]->SetTransform(&GoodZoom);
			fclose(fp);
			fp=NULL;
		}

		swprintf(greatfilepath, greatlength, L"..\\Resource\\Great\\%02d.png", i);

		_wfopen_s(&fp, greatfilepath, L"r");
		if(fp!=NULL){

			D3DXCreateSprite(d3ddev, &NoteGreatSprite[i]);
			D3DXGetImageInfoFromFile(greatfilepath, &NoteImageInfo);
			D3DXCreateTextureFromFileEx(d3ddev, greatfilepath, NoteImageInfo.Width, NoteImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &NoteGreatTexture[i]);

			greatx[i]=100.0f*exp/FLOAT(NoteImageInfo.Width);
			greaty[i]=100.0f*exp/FLOAT(NoteImageInfo.Height);
			D3DXMATRIX GreatZoom;

			D3DXMatrixTranslation(&GreatZoom, 0.0f, 0.0f, 0.0f);
			D3DXMatrixScaling(&GreatZoom, greatx[i], greaty[i], 0.0f);

			NoteGreatSprite[i]->SetTransform(&GreatZoom);
			fclose(fp);
			fp=NULL;
		}

		swprintf(failfilepath, faillength, L"..\\Resource\\Fail\\%02d.png", i);


		_wfopen_s(&fp, failfilepath, L"r");
		if(fp!=NULL){
			D3DXCreateSprite(d3ddev, &NoteFailSprite[i]);
			D3DXGetImageInfoFromFile(failfilepath, &NoteImageInfo);
			D3DXCreateTextureFromFileEx(d3ddev, failfilepath, NoteImageInfo.Width, NoteImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &NoteFailTexture[i]);

			failx[i]=100.0f*exp/FLOAT(NoteImageInfo.Width);
			faily[i]=100.0f*exp/FLOAT(NoteImageInfo.Height);
			D3DXMATRIX FailZoom;

			D3DXMatrixTranslation(&FailZoom, 0.0f, 0.0f, 0.0f);
			D3DXMatrixScaling(&FailZoom, failx[i], faily[i], 0.0f);

			NoteFailSprite[i]->SetTransform(&FailZoom);
			fclose(fp);
			fp=NULL;
		}

		swprintf(fastfilepath, fastlength, L"..\\Resource\\Fast\\%02d.png", i);

		_wfopen_s(&fp, fastfilepath, L"r");
		if(fp!=NULL){

			D3DXCreateSprite(d3ddev, &NoteFastSprite[i]);
			D3DXGetImageInfoFromFile(fastfilepath, &NoteImageInfo);
			D3DXCreateTextureFromFileEx(d3ddev, fastfilepath, NoteImageInfo.Width, NoteImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &NoteFastTexture[i]);

			fastx[i]=100.0f*exp/FLOAT(NoteImageInfo.Width);
			fasty[i]=100.0f*exp/FLOAT(NoteImageInfo.Height);
			D3DXMATRIX FastZoom;

			D3DXMatrixTranslation(&FastZoom, 0.0f, 0.0f, 0.0f);
			D3DXMatrixScaling(&FastZoom, fastx[i], fasty[i], 0.0f);

			NoteFastSprite[i]->SetTransform(&FastZoom);
			fclose(fp);
			fp=NULL;
		}
	}

	D3DXCreateSprite(d3ddev, &ClearSprite);
	D3DXCreateSprite(d3ddev, &FailedSprite);
	D3DXGetImageInfoFromFile(L"..\\Resource\\clear.png", &NoteImageInfo);
	D3DXCreateTextureFromFileEx(d3ddev, L"..\\Resource\\clear.png", NoteImageInfo.Width, NoteImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &ClearTexture);

	clearx=720*exp/FLOAT(NoteImageInfo.Width);
	cleary=120*exp/FLOAT(NoteImageInfo.Height);
	D3DXMATRIX ClearZoom;
	D3DXMatrixTranslation(&ClearZoom, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&ClearZoom, clearx, cleary, 0.0f);
	ClearSprite->SetTransform(&ClearZoom);

	D3DXGetImageInfoFromFile(L"..\\Resource\\failed.png", &NoteImageInfo);
	D3DXCreateTextureFromFileEx(d3ddev, L"..\\Resource\\failed.png", NoteImageInfo.Width, NoteImageInfo.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &FailedTexture);

	failedx=720*exp/FLOAT(NoteImageInfo.Width);
	failedy=120*exp/FLOAT(NoteImageInfo.Height);

	D3DXMATRIX FailedZoom;
	D3DXMatrixTranslation(&FailedZoom, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&FailedZoom, failedx, failedy, 0.0f);
	FailedSprite->SetTransform(&FailedZoom);

	startherebutton=new Button(d3ddev, L"..\\Resource\\starthere.png", exp);

	for(i=0;i<10;i++){
		swprintf_s(numpath, numlength, L"..\\Resource\\num_%d.png", i);
		num[i]=new Num(d3ddev, numpath, exp);
	}

	free(introfilepath);
	free(perfectfilepath);
	free(goodfilepath);
	free(greatfilepath);
	free(failfilepath);
	free(fastfilepath);
	free(numpath);
}

void Note::CreateNote(Music* _music){
	rankstatus=NON;
	combo=0;
	maxcombo=0;
	bonus=0.0f;
	perfectscore=0.0f;
	greatscore=0.0f;
	goodscore=0.0f;
	badscore=0.0f;
	score=0.0f;
	bonuscounter=0.0f;

	music=_music;
	int i, j, k;

	wchar_t* fname;
	int length=wcslen(L"..\\Note\\.not")+wcslen(music->GetFileName())+1;
	int temp;
	bool tempdata[16];
	fname=(wchar_t*)malloc(sizeof(wchar_t)*(length));
	swprintf_s(fname, length, L"..\\Note\\%s.not", music->GetFileName());
	_wfopen_s(&fp, fname, L"rb");
	if(fp==NULL){return;}
	free(fname);
	fread(&temp, sizeof(int), 1, fp);
	if(temp!=0x9BEA2123){
		fclose(fp);
		fp=NULL;
		return;
	}
	fread(&size, sizeof(int), 1, fp);
	fread(&temp, sizeof(int), 1, fp);
	if(temp!=0x2E0EDA2A){
		fclose(fp);
		fp=NULL;
		size=0;
		return;
	}
	for(j=0;j<16;j++){
		notevector[j].resize(size);
		notevector[j].clear();
		tempdata[j]=false;
		starthere[j]=false;
	}
	int tempnotedata[10];
	for(i=0; i<size; i++){
		fread(tempnotedata, sizeof(int), 10, fp);
		for(j=0;j<10;j++){
			if(tempnotedata[j]==0){continue;}
			else{
				tempdata[tempnotedata[j]-1]=true;
			}
		}
		for(k=0;k<16;k++){
			notevector[k].push_back(tempdata[k]);
			tempdata[k]=false;
		}
	}
	startflag=false;
	Count();
	maxcombofloat=(float)maxcombo;
	perfectscore=900000.0f/maxcombofloat;
	greatscore=perfectscore*0.7f;
	goodscore=perfectscore*0.4f;
	badscore=perfectscore*0.1f;
	bonus=1000000.0f-(perfectscore*maxcombofloat);
	rankbutton=NULL;
}

void Note::DeleteNote(){
	rankstatus=NON;
	int i;
	if(fp!=NULL){fclose(fp);}
	fp=NULL;
	for(i=0;i<16;i++){
		notevector[i].resize(0);
		notevector[i].clear();
		notestruct[i].notecount=0;
		notestruct[i].status=NONE;
		notestruct[i].count=0;
		starthere[i]=false;
	}
	startflag=false;
	size=0;
	location=0;
	music=NULL;
	
	combo=0;
	maxcombo=0;
	bonus=0.0f;
	perfectscore=0.0f;
	greatscore=0.0f;
	goodscore=0.0f;
	badscore=0.0f;
	score=0.0f;
	bonuscounter=0.0f;
	if(rankbutton!=NULL){delete rankbutton;}
	rankbutton=NULL;
}

void Note::DrawNoteSprite(FLOAT x, FLOAT y, LPD3DXSPRITE Sprite, LPDIRECT3DTEXTURE9 Texture, FLOAT mx, FLOAT my){
	D3DXVECTOR3 vector((left+x*hspace)/mx, (up+y*vspace)/my,0.0f);
	Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	Sprite->Draw(Texture, NULL, NULL, &vector, 0xFFFFFFFF);
	Sprite->End();
}

void Note::DrawNote(){
	int a, b, c, i;
	for(i=0;i<16;i++){
		if(notestruct[i].notecount!=0){
			c=notestruct[i].count;
			if(c!=0){
				a=i%4;
				b=i/4;
				switch(notestruct[i].status){
				case NONE:
					break;
				case INTRO:
					c=25-c;
					DrawNoteSprite(FLOAT(a), FLOAT(b), NoteIntroSprite[c], NoteIntroTexture[c], introx[c], introy[c]);
					break;
				case PERFECT:
					c=11-c;
					DrawNoteSprite(FLOAT(a), FLOAT(b), NotePerfectSprite[c], NotePerfectTexture[c], perfectx[c], perfecty[c]);
					break;
				case GOOD:
					c=11-c;
					DrawNoteSprite(FLOAT(a), FLOAT(b), NoteGoodSprite[c], NoteGoodTexture[c], goodx[c], goody[c]);
					break;
				case GREAT:
					c=11-c;
					DrawNoteSprite(FLOAT(a), FLOAT(b), NoteGreatSprite[c], NoteGreatTexture[c], greatx[c], greaty[c]);
					break;
				case FAIL:
					c=11-c;
					DrawNoteSprite(FLOAT(a), FLOAT(b), NoteFailSprite[c], NoteFailTexture[c], failx[c], faily[c]);
					break;
				case FAST:
					c=11-c;
					DrawNoteSprite(FLOAT(a), FLOAT(b), NoteFastSprite[c], NoteFastTexture[c], fastx[c], fasty[c]);
					break;
				}
			}
		}
	}
}

bool Note::NextNote(int* pcount){
	int i;
	(*pcount)%=6;
	int count=*pcount;

	if(count%3==0){
		for(i=0;i<16;i++){
			if(notestruct[i].notecount!=0){
				notestruct[i].notecount--;
				if(notestruct[i].count!=0){
					notestruct[i].count--;
					if(notestruct[i].count==0){
						if(notestruct[i].status==INTRO){
							notestruct[i].status=NONE;
							combo=0;
							bonuscounter-=(4/maxcombofloat);
						}
					}
				}
			}
		}
	}
	if(count==0){

		if(location<size){
			for(i=0;i<16;i++){
				if(notevector[i][location]&&notestruct[i].notecount==0){
					notestruct[i].notecount=40;
					notestruct[i].status=INTRO;
					notestruct[i].count=25;
					if(startflag){startflag=false;}
				}
			}
		}

		location++;
	}

	(*pcount)++;


	if(location==size+10){SSound();}
	if(location==size+30){
		bonus*=bonuscounter;
		return true;
	}
	else{return false;}
}

void Note::keyinput(const int i){
	int a, b;
	a=i%4;
	b=i/4;

	if(notestruct[i].status==INTRO){
		if(notestruct[i].count>0&&notestruct[i].count<=25){
			switch(notestruct[i].count){/*
										case 1:
										case 2:
										case 3:
										notestruct[i].status=FAIL;
										break;
										case 4:
										case 5:
										notestruct[i].status=GOOD;
										break;
										case 6:
										case 7:
										notestruct[i].status=GREAT;
										break;
										case 8:
										case 9:
										notestruct[i].status=PERFECT;
										break;
										case 10:
										case 11:
										case 12:
										notestruct[i].status=GREAT;
										break;
										case 13:
										case 14:
										case 15:
										notestruct[i].status=GOOD;
										break;
										default:
										notestruct[i].status=FAST;
										break;*/

			case 1:
			case 2:
			case 3:
			case 4:
			case 5:

				notestruct[i].status=FAIL;
				score+=badscore;
				combo=0;
				bonuscounter-=(4/maxcombofloat);
				break;
			case 6:

				notestruct[i].status=GOOD;
				combo++;
				score+=goodscore;
				bonuscounter+=(1/maxcombofloat);
				break;
			case 7:

				notestruct[i].status=GREAT;
				combo++;
				score+=greatscore;
				bonuscounter+=(2/maxcombofloat);
				break;
			case 8:
			case 9:
			case 10:
				notestruct[i].status=PERFECT;
				combo++;
				score+=perfectscore;
				bonuscounter+=(2/maxcombofloat);
				break;

			case 11:
			case 12:

				notestruct[i].status=GREAT;
				combo++;
				score+=greatscore;
				bonuscounter+=(2/maxcombofloat);
				break;
			case 13:
			case 14:
			case 15:

				notestruct[i].status=GOOD;
				combo++;
				score+=goodscore;
				bonuscounter+=(1/maxcombofloat);
				break;
			default:

				notestruct[i].status=FAST;
				combo=0;
				score+=badscore;
				bonuscounter-=(4/maxcombofloat);
				break;
			}
			notestruct[i].count=11;
		}
	}
}

void Note::PSound(){
	music->Play();
}

void Note::SSound(){
	music->Stop();
}

void Note::Count(){
	int location0=0;
	int i=0;
	int counts[16]={0,};

	int count5=0;

	while(location0<size){

		if(count5%3==0){
			for(i=0;i<16;i++){
				if(counts[i]!=0){
					counts[i]--;
				}
			}
		}
		if(count5==0){

			if(location0<size){
				for(i=0;i<16;i++){
					if(notevector[i][location0]&&counts[i]==0){
						counts[i]=40;
						maxcombo++;
						if(!startflag){
							startflag=true;
							for(int j=0;j<16;j++){
								starthere[j]=notevector[j][location0];
							}
						}
					}
				}
			}

			location0++;
		}
		count5++;
		count5%=6;
	}
}

void Note::CalcScore(){
	if(bonuscounter<0.0f){
		bonuscounter=0.0f;
	}
	if(bonuscounter>1.0f){
		bonuscounter=1.0f;
	}
}

void Note::DrawResult(){
	switch(rankstatus){
	case F:
		DrawFailed();
		if(rankbutton==NULL){
			rankbutton=new Button(d3ddev, L"..\\Resource\\rank_f.png", exp);
		}
		break;
	case C:
		DrawClear();
		if(rankbutton==NULL){
			rankbutton=new Button(d3ddev, L"..\\Resource\\rank_c.png", exp);
			break;
	case B:
		DrawClear();
		if(rankbutton==NULL){
			rankbutton=new Button(d3ddev, L"..\\Resource\\rank_b.png", exp);
		}
		break;
	case A:
		DrawClear();
		if(rankbutton==NULL){
			rankbutton=new Button(d3ddev, L"..\\Resource\\rank_a.png", exp);
		}
		break;
	case S:
		DrawClear();
		if(rankbutton==NULL){
			rankbutton=new Button(d3ddev, L"..\\Resource\\rank_s.png", exp);
		}
		break;
	case SS:
		DrawClear();
		if(rankbutton==NULL){
			rankbutton=new Button(d3ddev, L"..\\Resource\\rank_ss.png", exp);
		}
		break;
	case SSS:
		DrawClear();
		if(rankbutton==NULL){
			rankbutton=new Button(d3ddev, L"..\\Resource\\rank_sss.png", exp);
		}
		break;
	case EX:
		DrawClear();
		if(rankbutton==NULL){
			rankbutton=new Button(d3ddev, L"..\\Resource\\rank_exc.png", exp);
		}
		break;
	default:
		if(rankbutton!=NULL){
			delete rankbutton;
			rankbutton=NULL;
		}
		break;
		}
	}
	if(rankbutton!=NULL){
		rankbutton->DrawButton(2.0f, 2.0f);
	}
}

void Note::PrintCombo(){
	int tempcombo=combo%100000;
	int i;
	float f=0.0f;
	int numi[5];
	if(combo>=10000){
		for(i=0;i<5;i++){
			numi[i]=tempcombo%10;
			tempcombo/=10;

			num[numi[i]]->DrawNum(3.2f-(0.8f*f), 1.1f);
			f+=1.0f;
		}
	}
	else if(combo>=1000){
		for(i=0;i<4;i++){
			numi[i]=tempcombo%10;
			tempcombo/=10;

			num[numi[i]]->DrawNum(3.0f-f, 1.1f);
			f+=1.0f;
		}
	}
	else if(combo>=100){
		for(i=0;i<3;i++){
			numi[i]=tempcombo%10;
			tempcombo/=10;

			num[numi[i]]->DrawNum(2.5f-f, 1.1f);
			f+=1.0f;
		}
	}
	else if(combo>=10){
		for(i=0;i<2;i++){
			numi[i]=tempcombo%10;
			tempcombo/=10;

			num[numi[i]]->DrawNum(2.0f-f, 1.1f);
			f+=1.0f;
		}
	}
	else if(combo!=0){
		num[tempcombo]->DrawNum(1.5f, 1.1f);
	}
}

void Note::DrawScore(){
	wchar_t scorestr[16];
	swprintf_s(scorestr, 16, L"%.0f 점", score);
	RECT rc={fleft, fup, fright, fdown};
	FontSprite->Begin(D3DXSPRITE_ALPHABLEND);
	Font->DrawTextW(FontSprite, scorestr, wcslen(scorestr), &rc, DT_RIGHT | DT_SINGLELINE | DT_NOCLIP, D3DCOLOR_XRGB(fcr, fcg, fcb));
	FontSprite->End();
}

bool Note::CalCBonusScore(){
	if(bonus>=5556.0f){
		bonus-=5556.0f;
		score+=5556.0f;
		return false;
	}
	else if(bonus>0.0f){
		score+=bonus;
		bonus=0.0f;
		return false;
	}
	else{
		return true;
	}
}

void Note::CalcRank(){
	if(score<700000){
		rankstatus=F;
	}
	else if(score<800000){
		rankstatus=C;
	}
	else if(score<850000){
		rankstatus=B;
	}
	else if(score<900000){
		rankstatus=A;
	}
	else if(score<950000){
		rankstatus=S;
	}
	else if(score<980000){
		rankstatus=SS;
	}
	else if(score<1000000){
		rankstatus=SSS;
	}
	else{
		rankstatus=EX;
	}
}

void Note::DrawClear(){
	D3DXVECTOR3 tempvector(-120.0f/clearx*exp, 230.0f/cleary*exp, 0.0f);
	ClearSprite->Begin(D3DXSPRITE_ALPHABLEND);
	ClearSprite->Draw(ClearTexture, NULL, NULL, &tempvector, 0xFFFFFFFF);
	ClearSprite->End();
}

void Note::DrawFailed(){
	
	D3DXVECTOR3 tempvector(-120.0f/clearx*exp, 230.0f/cleary*exp, 0.0f);
	FailedSprite->Begin(D3DXSPRITE_ALPHABLEND);
	FailedSprite->Draw(FailedTexture, NULL, NULL, &tempvector, 0xFFFFFFFF);
	FailedSprite->End();
}

void Note::DrawStarthere(){
	if(startflag){
		for(int i=0;i<16;i++){
			if(starthere[i]){
				startherebutton->DrawButton(float(i%4), float(i/4));
			}
		}
	}
}