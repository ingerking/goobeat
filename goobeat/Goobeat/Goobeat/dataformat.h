#pragma once

struct Data_T{
	double louder;
	int num;
	bool operator<(Data_T& a){return (louder<a.louder?true:false);}
};
