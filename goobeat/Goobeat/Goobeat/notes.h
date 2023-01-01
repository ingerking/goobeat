#pragma once

#include "waveformat.h"
#include "dataformat.h"
#include "2darray.h"
#include "waveanalysismatrix.h"
#include "sincosmake.h"
#include <vector>
#include <fstream>
#include <string.h>
#include <wchar.h>
#include "bass.h"
#include <locale.h>

#pragma comment (lib, "bass")


using namespace std;

class Note_T
{
private:
	CHUNK* chunk;
	RIFF* riff;
	FORMAT* format;
	FACT* fact;
	FILE* fp;
	FILE* fpout;
	double* cosarray;
	double* sinarray;
	unsigned int alldatasize;
	int samplelong;
	int datasize;
	bool fileexists;
	bool newfilecreated;
	wchar_t* fname;
	wchar_t* path;


	//vector<vector<Data_T>*>* data;
public:
	Note_T(const wchar_t* _fname, const wchar_t* _path);
	~Note_T(){
		if(fname!=NULL){delete fname;}
		if(path!=NULL){delete path;}
		if(chunk!=NULL){free(chunk);}
		if(riff!=NULL){free(riff);}
		if(format!=NULL){free(format);}
		if(fact!=NULL){free(fact);}
		if(fp!=0){fclose(fp);}
		if(fpout!=0){fclose(fpout);}
		if(newfilecreated){
			free_vector<double>(cosarray);
			free_vector<double>(sinarray);
		}
	}
	bool MakeData(double loud, double magnification);
	bool filecheck(FILE* checkfile);
	bool fileavailable(){return fileexists;}
	FORMAT* getformat(){return format;}
	bool mp3analysis(double loud, double magnification);
};