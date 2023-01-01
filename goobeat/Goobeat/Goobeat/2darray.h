#pragma once
#include<stdlib.h>

template<typename T>

T* vector_space(int size){
	T* cm;
	cm=(T*)calloc(size, sizeof(T));
	return cm;
}

template<typename T>
void free_vector(T* cm){
	free(cm);
}

template<typename T>
T** matrix_space(int height, int width){
	T** cm;
	cm=(T**)calloc(height,sizeof(T*));

	for(int i=0;i<height;i++){
		cm[i]=(T*)calloc(width,sizeof(T));
	}
	return cm;
}

template<typename T>
void free_matrix(T** cm, int height){
	for(int i=0;i<height;i++){
		free(cm[i]);
	}
	free(cm);
}