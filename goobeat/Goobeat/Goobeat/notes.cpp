#include "notes.h"//fprintf를 fwrite로 모두 바꿀것
#include <stdio.h>

Note_T::Note_T(const wchar_t* _fname, const wchar_t* _path){
	fname=NULL;
	path=NULL;

	int flenth=wcslen(_fname)+1;
	int plenth=wcslen(_path)+1;

	fname=(wchar_t*)malloc(sizeof(wchar_t)*flenth);
	path=(wchar_t*)malloc(sizeof(wchar_t)*plenth);
	swprintf_s(fname, flenth, L"%s", _fname);
	swprintf_s(path, plenth, L"%s", _path);

	riff=NULL;
	format=NULL;
	fact=NULL;
	chunk=NULL;
	fileexists=false;
	newfilecreated=false;
	_wfopen_s(&fp, fname,L"rb");
	wchar_t* tempfname=(wchar_t*)malloc(sizeof(wchar_t)*(wcslen(path)+wcslen(fname)+wcslen(L"\\.not")+1));
	swprintf_s(tempfname, wcslen(path)+wcslen(fname)+wcslen(L"\\.not")+1, L"%s\\%s.not", path, fname);
	if(_wfopen_s(&fpout, tempfname,L"rb")!=0){
		_wfopen_s(&fpout, tempfname,L"wb");
	}
	else{
		fileexists=filecheck(fpout);
		if(!fileexists){
			fclose(fpout);
			_wfopen_s(&fpout, tempfname,L"wb");
		}
	}
	free(tempfname);
}

bool Note_T::MakeData(double loud, double magnification){
	if(!fileexists){
		riff=(RIFF *)malloc(sizeof(RIFF));
		if( 1 == fread(riff,sizeof(RIFF),1,fp) ) {
			chunk=read_chunk(fp);
			while(chunk!=0){
				switch(chunk->id){
				case 0x20746D66:
					format=(FORMAT*)chunk;
					chunk=read_chunk(fp);
					break;
				case 0x74636166:
					fact=(FACT*)chunk;
					chunk=read_chunk(fp);
					break;
				case 0x61746164:
					alldatasize=chunk->size;
					samplelong=format->BytesPerSec/20;
					datasize=alldatasize/samplelong/2;
					chunk=0;
					break;
				default:
					fileexists=false;
					return false;
				}
			}
		}

		cosarray=makecos_f(samplelong);
		sinarray=makesin_f(samplelong);


		//		data=new vector<vector<Data_T>*>(datasize+1);
		//		data->clear();

		int projectid=0x9BEA2123;
		int projectsize=datasize+1;
		int dataid=0x2E0EDA2A;

		fwrite(&projectid, 1, sizeof(int), fpout);
		fwrite(&projectsize, 1, sizeof(int), fpout);
		fwrite(&dataid, 1, sizeof(int), fpout);

		vector<Data_T>::iterator iter;
		Data_T tempbinarydata;
		int templouder;

		long double louders=0.0;

		vector<vector<Data_T>*> temptempvector;
		temptempvector.resize(datasize);
		temptempvector.clear();

		short* tempdata=vector_space<short>(samplelong);
		for(int i=0;i<datasize;i++){
			fread(tempdata,sizeof(short),samplelong,fp);
			if(feof(fp)) break;
			vector<Data_T>* tempvector=wave_analysis<short>(tempdata, samplelong, cosarray, sinarray);

			temptempvector.push_back(tempvector);
			//			data->push_back(tempvector);
			for(iter=tempvector->begin();iter!=tempvector->end();iter++){
				tempbinarydata=*iter;
				if(tempbinarydata.num==0){
					louders+=tempbinarydata.louder;
					break;
				}
			}
		}
		louders/=(double)datasize;
		if(louders>=1100){
			long double a1=(1000.0/log(10.0))*(log(5.0)+log(louders-1000.0))-2500.0;
			long double a2=850.0*atan((louders-1100.0)*0.005);
			louders=0.5*a1+0.5*a2;
		}
		else{
			louders=-5000.0*cos(louders/3000.0)+5000.0;
		}
		louders*=loud;
		
		vector<vector<Data_T>*>::iterator iter3;
		for(iter3=temptempvector.begin();iter3!=temptempvector.end();iter3++){
			vector<Data_T>* tempvector3=*iter3;
			for(iter=tempvector3->begin();iter!=tempvector3->end();iter++){
				tempbinarydata=*iter;
				if(tempbinarydata.num==0){
					break;
				}
				if(tempbinarydata.louder>=(magnification*louders+(*tempvector3)[11].louder*(1.0-magnification))){
					templouder=((int)tempbinarydata.louder%16)+1;
				}
				else{
					templouder=0;
				}
				fwrite(&templouder, 1, sizeof(int), fpout);
			}
			delete(tempvector3);
		}
		free_vector(tempdata);
		tempdata=vector_space<short>(samplelong);
		fread(tempdata,sizeof(short),samplelong,fp);


		vector<Data_T>* tempvector=wave_analysis<short>(tempdata, samplelong, cosarray, sinarray);

		//		data->push_back(tempvector);
		for(iter=tempvector->begin();iter!=tempvector->end();iter++){
			tempbinarydata=*iter;
			if(tempbinarydata.louder>=(magnification*louders+(*tempvector)[11].louder*(1.0-magnification))){
				templouder=((int)tempbinarydata.louder%16)+1;
			}
			else{
				templouder=0;
			}
			fwrite(&templouder, 1, sizeof(int), fpout);
		}


		//		data->push_back(tempvector);

		free_vector(tempdata);
		delete(tempvector);
		fileexists=true;
		newfilecreated=true;
		return true;
	}
	else{
		return true;
	}
}

bool Note_T::filecheck(FILE* checkfile){
	int projectid;
	int size;
	int dataid;
	fread(&projectid,sizeof(int),1,checkfile);
	fread(&size,sizeof(int),1,checkfile);
	fread(&dataid,sizeof(int),1,checkfile);

	if(projectid!=0x9BEA2123){return false;}
	if(dataid!=0x2E0EDA2A){return false;}
	return true;
}

bool Note_T::mp3analysis(double loud, double magnification){
	if(!fileexists){
		BASS_CHANNELINFO info;
		DWORD chan,p;
		QWORD pos;
		WAVEFORMATEX wf;
		char* fnamemb;
		int charlenth=2*wcslen(fname)+1;
		fnamemb=(char*)malloc(charlenth);

		size_t aaaa=charlenth;

		wcstombs_s(&aaaa, fnamemb, charlenth, fname, charlenth);
	//	wcstombs(fnamemb, fname, charlenth);
		// check the correct BASS was loaded
		if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
		free(fnamemb);
			return false;
		}

		// not playing anything, so don't need an update thread
		BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD,0);

		// setup output - "no sound" device, 44100hz, stereo, 16 bits
		if (!BASS_Init(0,44100,0,0,NULL)){
		free(fnamemb);
		BASS_Free();
			return false;
		}

		// try streaming the file/url
		if ((chan=BASS_StreamCreateFile(FALSE,fnamemb,0,0,BASS_STREAM_DECODE))
			|| (chan=BASS_StreamCreateURL(fnamemb,0,BASS_STREAM_DECODE|BASS_STREAM_BLOCK,0,0))) {
				pos=BASS_ChannelGetLength(chan,BASS_POS_BYTE);

		} else {
			// try loading the MOD (with sensitive ramping, and calculate the duration)
			if (!(chan=BASS_MusicLoad(FALSE,fnamemb,0,0,BASS_MUSIC_DECODE|BASS_MUSIC_RAMP|BASS_MUSIC_PRESCAN,0))){
				// not a MOD either

				free(fnamemb);
				BASS_Free();
				return false;
			}
			{ // count channels
				float dummy;
				for (p=0;BASS_ChannelGetAttribute(chan,BASS_ATTRIB_MUSIC_VOL_CHAN+p,&dummy);p++);
			}
			pos=BASS_ChannelGetLength(chan,BASS_POS_BYTE);
		}

		// display the time length
		if (pos && pos!=-1) {
			p=(DWORD)BASS_ChannelBytes2Seconds(chan,pos);
		} 

		// write WAV header
		BASS_ChannelGetInfo(chan,&info);
		wf.wFormatTag=1;
		wf.nChannels=info.chans;
		wf.wBitsPerSample=(info.flags&BASS_SAMPLE_8BITS?8:16);
		wf.nBlockAlign=wf.nChannels*wf.wBitsPerSample/8;
		wf.nSamplesPerSec=info.freq;
		wf.nAvgBytesPerSec=wf.nSamplesPerSec*wf.nBlockAlign;
#ifdef _BIG_ENDIAN // swap byte order
		wf.wFormatTag=le_16(wf.wFormatTag);
		wf.nChannels=le_16(wf.nChannels);
		wf.wBitsPerSample=le_16(wf.wBitsPerSample);
		wf.nBlockAlign=le_16(wf.nBlockAlign);
		wf.nSamplesPerSec=le_32(wf.nSamplesPerSec);
		wf.nAvgBytesPerSec=le_32(wf.nAvgBytesPerSec);
#endif
		alldatasize=BASS_ChannelGetLength(chan,BASS_POS_BYTE);
		samplelong=wf.nAvgBytesPerSec/20;

		datasize=alldatasize/samplelong/2;




		cosarray=makecos_f(samplelong);
		sinarray=makesin_f(samplelong);


		int projectid=0x9BEA2123;
		int projectsize=datasize+1;
		int dataid=0x2E0EDA2A;

		fwrite(&projectid, 1, sizeof(int), fpout);
		fwrite(&projectsize, 1, sizeof(int), fpout);
		fwrite(&dataid, 1, sizeof(int), fpout);

		vector<Data_T>::iterator iter;
		Data_T tempbinarydata;
		int templouder;

		long double louders=0.0;

		vector<vector<Data_T>*> temptempvector;
		temptempvector.resize(datasize);
		temptempvector.clear();



		short* tempdata=vector_space<short>(samplelong);
		for(int i=0;i<datasize;i++){
			int c=BASS_ChannelGetData(chan,tempdata,samplelong);
			if(c==0) break;
			vector<Data_T>* tempvector=wave_analysis<short>(tempdata, samplelong, cosarray, sinarray);

			temptempvector.push_back(tempvector);
			//			data->push_back(tempvector);
			for(iter=tempvector->begin();iter!=tempvector->end();iter++){
				tempbinarydata=*iter;
				if(tempbinarydata.num==0){
					louders+=tempbinarydata.louder;
					break;
				}
			}
		}
		louders/=(double)datasize;
		
		if(louders>=1100){
			long double a1=(1000.0/log(10.0))*(log(5.0)+log(louders-1000.0))-2500.0;
			long double a2=850.0*atan((louders-1100.0)*0.005);
			louders=0.5*a1+0.5*a2;
		}
		else{
			louders=-5000.0*cos(louders/3000.0)+5000.0;
		}
		louders*=loud;

		vector<vector<Data_T>*>::iterator iter3;
		for(iter3=temptempvector.begin();iter3!=temptempvector.end();iter3++){
			vector<Data_T>* tempvector3=*iter3;
			for(iter=tempvector3->begin();iter!=tempvector3->end();iter++){
				tempbinarydata=*iter;
				if(tempbinarydata.num==0){
					break;
				}
				if(tempbinarydata.louder>=(magnification*louders+(*tempvector3)[11].louder*(1.0-magnification))){
					templouder=((int)tempbinarydata.louder%16)+1;
				}
				else{
					templouder=0;
				}
				fwrite(&templouder, 1, sizeof(int), fpout);
			}
			delete(tempvector3);
		}
		free_vector(tempdata);
		//		tempdata=vector_space<short>(samplelong);
		//		fread(tempdata,sizeof(short),samplelong,fp);


		vector<Data_T>* tempvector=wave_analysis<short>(tempdata, samplelong, cosarray, sinarray);

		//		data->push_back(tempvector);
		for(iter=tempvector->begin();iter!=tempvector->end();iter++){
			tempbinarydata=*iter;
			if(tempbinarydata.louder>=(magnification*louders+(*tempvector)[11].louder*(1.0-magnification))){
				templouder=((int)tempbinarydata.louder%16)+1;
			}
			else{
				templouder=0;
			}
			fwrite(&templouder, 1, sizeof(int), fpout);
		}


		//		data->push_back(tempvector);

		//		free_vector(tempdata);
		delete(tempvector);
		fileexists=true;
		newfilecreated=true;

		// complete WAV header
		free(fnamemb);
		BASS_Free();
		return true;
	}
	else{
		return true;
	}
}