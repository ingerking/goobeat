#include"sincosmake.h"

double* makecos_f(const int length){
	double* cosvalue=vector_space<double>(length);
	cosvalue[0]=(double)1;

	const int quat=length/4;
	const int di=length/2;


	if(length%4==0){
		for(int i=1;i<=quat;i++){
			cosvalue[i]=cos(2*i*pi/length);
		}
		for(int i=1;i<quat;i++){
			cosvalue[quat+i]=-cosvalue[quat-i];
		}
		for(int i=0;i<di;i++){
			cosvalue[di+i]=-cosvalue[i];
		}
	}
	else if(length%4==2){
		for(int i=1;i<=quat;i++){
			cosvalue[i]=cos(2*i*pi/length);
		}
		for(int i=0;i<quat;i++){
			cosvalue[quat+i+1]=-cosvalue[quat-i];
		}
		for(int i=0;i<di;i++){
			cosvalue[di+i]=-cosvalue[i];
		}
	}
	else{
		for(int i=1;i<=di;i++){
			cosvalue[i]=cos(2*i*pi/length);
		}
		for(int i=0;i<di;i++){
			cosvalue[di+i+1]=cosvalue[di-i];
		}
	}
	return cosvalue;
}

double* makesin_f(const int length){
	double* sinvalue=vector_space<double>(length);
	sinvalue[0]=(double)0;

	
	const int quat=length/4;
	const int di=length/2;


	if(length%4==0){
		for(int i=1;i<=quat;i++){
			sinvalue[i]=sin(2*i*pi/length);
		}
		for(int i=1;i<quat;i++){
			sinvalue[quat+i]=sinvalue[quat-i];
		}
		for(int i=0;i<di;i++){
			sinvalue[di+i]=-sinvalue[i];
		}
	}
	else if(length%4==2){
		for(int i=1;i<=quat;i++){
			sinvalue[i]=sin(2*i*pi/length);
		}
		for(int i=0;i<quat;i++){
			sinvalue[quat+i+1]=sinvalue[quat-i];
		}
		for(int i=0;i<di;i++){
			sinvalue[di+i]=-sinvalue[i];
		}
	}
	else{
		for(int i=1;i<=di;i++){
			sinvalue[i]=sin(2*i*pi/length);
		}
		for(int i=0;i<di;i++){
			sinvalue[di+i+1]=-sinvalue[di-i];
		}
	}
	return sinvalue;
}