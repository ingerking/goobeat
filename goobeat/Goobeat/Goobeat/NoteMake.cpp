#include "NoteMake.h"
#include <wchar.h>
#include <io.h>

bool compare(Music* a, Music* b){
	return (wcscmp(a->GetFileName(), b->GetFileName())<0? true: false);
}

void NoteMake::MakeNoteWav(vector<Music*>* tempvector, const wchar_t * inputpath, const wchar_t* outputpath, double loud, double magnification){
	_wchdir(inputpath);
	struct _wfinddata_t c_file;
	long hFile;
	hFile = (long)_wfindfirst( L"*.wav", &c_file);
	if(hFile==-1){return;}
	do {
		note=new Note_T(c_file.name, outputpath);
		if(note->MakeData(loud, magnification)){

		Music* tempmusic=new Music(c_file.name, true);
		tempvector->push_back(tempmusic);
		}

		delete note;
	}while( _wfindnext( hFile, &c_file ) == 0 );
//	_findclose( hFile );
}

void NoteMake::MakeNoteMp3(vector<Music*>* tempvector, const wchar_t * inputpath, const wchar_t* outputpath, double loud, double magnification){
	_wchdir(inputpath);
	struct _wfinddata_t c_file;
	long hFile;
	hFile = (long)_wfindfirst( L"*.mp3", &c_file);
	if(hFile==-1){return;}
	do{
		note=new Note_T(c_file.name, outputpath);
		if(note->mp3analysis(loud, magnification)){

		Music* tempmusic=new Music(c_file.name, true);
		tempvector->push_back(tempmusic);
		}

		delete note;
	}while( _wfindnext( hFile, &c_file ) == 0 );
	_findclose( hFile );
}

void NoteMake::MakeNote(vector<Music*>* tempvector, const wchar_t * inputpath, const wchar_t* outputpath, double loud, double magnification){
	MakeNoteWav(tempvector, inputpath, outputpath, loud, magnification);
	MakeNoteMp3(tempvector, inputpath, outputpath, loud, magnification);

	sort(tempvector->begin(), tempvector->end(), compare);
}