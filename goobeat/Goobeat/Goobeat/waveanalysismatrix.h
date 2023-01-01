#pragma once

#include"2darray.h"
#include<math.h>
#include<vector>
#include<algorithm>
#include"dataformat.h"

template <typename T>
double* cos_analysis(const T* arrays, const int length, const double* cosvalue, int flag){
	double* result=vector_space<double>(length);
	int temp=(length>250?250:length);
	for(int i=0;i<temp;i++){
		for(int j=0;j<length;j+=flag){
			result[i]+=cosvalue[(i*j)%length]*(double)arrays[j];
		}
	}

	result[0]/=2;


	return result;
}



template <typename T>
double* sin_analysis(const T* arrays, const int length, const double* sinvalue, int flag){
	double* result=vector_space<double>(length);
	int temp=(length>250?250:length);
	for(int i=0;i<temp;i++){
		for(int j=0;j<length;j+=flag){
			result[i]+=sinvalue[(i*j)%length]*(double)arrays[j];
		}
	}

	result[0]=(double)0;


	return result;
	
}

template<typename T>
vector<Data_T>* wave_analysis(const T* arrays, const int length, const double* cosvalue, const double* sinvalue){
	double count=0.0;
	int flag=1;
	if(length%4==0){
		flag=4;
	}
	else if(length%2==0){
		flag=2;
	}
	else{flag=1;}
	
	double* a=NULL;
	double* b=NULL;
	vector<Data_T> c(length);
	c.clear();

	int lenth=length/flag;
	Data_T data0, data1;

	a=cos_analysis<T>(arrays, lenth, cosvalue, flag);
	b=sin_analysis<T>(arrays, lenth, sinvalue, flag);

	data0.num=0;
	for(int i=0;i<lenth;i++){
		Data_T temp;
		temp.louder=a[i]*a[i]+b[i]*b[i];
		temp.num=i+1;
		c.push_back(temp);
	}
	if(a!=NULL){free_vector(a);}
	if(b!=NULL){free_vector(b);}
	sort(c.begin(),c.end());
	vector<Data_T>* result=new vector<Data_T>(12);
	result->clear();
	for(int i=1;i<=10;i++){
		if(i<=5){
			Data_T tempdata;
			double temp=sqrt(c[lenth-i].louder);
			tempdata.louder=sqrt(temp);
			//			sqrt(temp);
			tempdata.num=c[lenth-i].num;
			result->push_back(tempdata);
			if(tempdata.louder>100){
				count+=1.0;
			}
		}
		else{
			Data_T tempdata;
			tempdata.louder=0.0;
			tempdata.num=c[lenth-i].num;
			result->push_back(tempdata);
		}

	}
	data0.louder=pow(c[lenth-1].louder, 0.3);
	result->push_back(data0);
	data1.num=0;
	if(count>0.5){
		data1.louder=data0.louder/count;
	}
	else{
		data1.louder=0.0;
	}
	result->push_back(data1);
	return result;
}