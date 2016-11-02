#include <cstdio>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <nmmintrin.h>

//compile: g++ -g wordbmh.cpp -o wordbmh -std=c++11 -msse4.2

std::list<int> wbmh(std::string text, std::string pat){
	//store starting index of occurrences here
	std::list<int> res;
	unsigned int patlen = pat.size();
	unsigned int strlen = text.size();
	
	//preprocess pattern
	int alphalen = 128; //ascii
	int delta12[alphalen];
	int j;
	for(j=0;j<alphalen;j++){
		delta12[j] = patlen;
	}
	for(j=0;j<patlen-1;j++){
		delta12[pat.at(j)] = patlen-j-1;
	}
	char lastch = pat.at(patlen-1);
	__m128i packedpat = _mm_loadu_si128 ((__m128i *) pat.c_str());
	//const char *s = astring.substr(0,16).c_str();
	unsigned int patleni = patlen-1;
	unsigned int i = patleni;
	
	while(i<strlen){
		__m128i window = text.substr(i-patleni,i).c_str();
		int ind = _mm_cmpistri(pat,window,mode);
		if(ind>patleni){
			//pattern found
			res.push_back(i-patleni);
			printf("found at: %d\n",i-patleni);
			i = i+delta12[lastch];
		}else{
			i = i+delta12[text.at(i-(patlen-ind)+1)];
		}
	}
	return res;
}

int main(){
	wbmh("banana","nana");
}
