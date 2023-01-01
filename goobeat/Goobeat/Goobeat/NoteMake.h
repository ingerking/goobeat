#include "notes.h"
#include <vector>
#include "Music.h"

using namespace std;

class NoteMake{
private:
	Note_T* note;

public:
	NoteMake(){;}
	~NoteMake(){;}
	void MakeNoteWav(vector<Music*>* tempvector, const wchar_t * inputpath, const wchar_t* outputpath, double loud, double magnification);
		//inputpath경로에 있는 wav파일에서 노트를 만듬. outpath경로에 저장
	void MakeNoteMp3(vector<Music*>* tempvector, const wchar_t * inputpath, const wchar_t* outputpath, double loud, double magnification);
		//mp3 "
	void MakeNote(vector<Music*>* tempvector, const wchar_t * inputpath, const wchar_t* outputpath, double loud, double magnification);
		
};