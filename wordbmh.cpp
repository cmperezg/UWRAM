#include <cstdio>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <nmmintrin.h>

#include <algorithm>
#include <fstream>



//compile: g++ -g wordbmh.cpp -o wordbmh -std=c++11 -msse4.2
const int mode = _SIDD_UBYTE_OPS|_SIDD_CMP_EQUAL_EACH|_SIDD_MOST_SIGNIFICANT|_SIDD_NEGATIVE_POLARITY;

void print128_ch(__m128i var){

    uint8_t *val = (uint8_t*) &var;
    printf("Text: %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c \n",
           val[0], val[1], val[2], val[3], val[4], val[5],
           val[6], val[7], val[8], val[9], val[10], val[11],
           val[12], val[13], val[14], val[15]);
}


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
	//std::cout<< delta12[lastch] << lastch <<"\n";
	//if(delta12[lastch]==0) delta12[lastch]=patlen;
	__m128i packedpat = _mm_loadu_si128 ((__m128i *) pat.c_str());
	//const char *s = astring.substr(0,16).c_str();
	unsigned int patleni = patlen-1;
	unsigned int i = patleni;
	int ind;
	
	while(i<strlen){
		__m128i window = _mm_loadu_si128 ((__m128i *)(text.substr(i-patleni,patlen).c_str()));
		ind = _mm_cmpestri(packedpat,patlen,window,patlen,mode);
		//std::cout << "substring: " << text.substr(i-patleni,patlen) << "\n";
		//std::cout<<"cmpistri: " << ind << "\n\n";
		if(ind>patleni){
			//pattern found
			res.push_back(i-patleni);
			//printf("found at: %d\n",i-patleni);
			//print128_ch(window);
			
			i = i+delta12[lastch];
		}else{
			i = i+delta12[text.at(i-(patlen-ind)+1)];
		}
	}
	return res;
}

void printResults(const std::list<int>& s){
	std::cout<< "found pattern at: ";
	std::list<int>::const_iterator i;
	for(i=s.begin();i!=s.end();++i){
		std::cout<<*i << " ";
	}
	std::cout<< "\n";
}

int main(){
	std::ifstream infile {"lidata10.txt"};
	std::string fst{std::istreambuf_iterator<char>(infile),std::istreambuf_iterator<char>()};

	std::transform(fst.begin(),fst.end(),fst.begin(),::tolower);
	
	std::string pattern = "vestibulum";
	
	//std::list<int> res = uwbmh(fst,pattern);
	printResults(wbmh(fst,pattern));
}
