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
		//inputpath��ο� �ִ� wav���Ͽ��� ��Ʈ�� ����. outpath��ο� ����
	void MakeNoteMp3(vector<Music*>* tempvector, const wchar_t * inputpath, const wchar_t* outputpath, double loud, double magnification);
		//mp3 "
	void MakeNote(vector<Music*>* tempvector, const wchar_t * inputpath, const wchar_t* outputpath, double loud, double magnification);
		
};