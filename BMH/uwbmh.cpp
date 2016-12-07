#include <cstdio>
#include <vector>
#include <chrono>
#include <tuple>
#include <list>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include "ultraword.h"


//compile: g++ uwbmh.cpp ultraword.cpp -o uwbmh -std=c++11

void printlongbits(unsigned long long int n){
	long long int i;
	for(i=63;i>=0;i--){
		unsigned long long int mask = ((unsigned long long int)1)<<i;
		unsigned long long int maskedn = n&mask;
		unsigned long long int thebit = maskedn >> i;
		printf("%u",(unsigned int)thebit);
		if(i%8==0){
			printf(" ");
		}
		//printf("%llu",n);
	}
	//printf("%llu",n);
	printf("\n");
}



void printUWc(UltraWord& u){
	unsigned long long int blocks[UltraWord::BLOCK_SIZE];
	unsigned long long int *a  = u.getBlocks();
	unsigned long long int mask8 = (unsigned long long int)0xFF<<56;
	int i;
	int j;
	for(i=0;i<UltraWord::NUM_BLOCKS;i++){
		blocks[i] = a[i];
	}
	for(i=0;i<UltraWord::NUM_BLOCKS;i++){

		for(j=0;j<(UltraWord::BLOCK_SIZE/8);j++){
			printf("%c",(int)(blocks[i]>>56));
			//printf("i: %d j: %d \n",i,j);
			//printlongbits(blocks[i]);
			blocks[i] = blocks[i]<<8;
		}
	}
	std::cout<< std::endl;
}

std::list<int> uwbmh(std::string text, std::string pat){
	std::list<int> res;
	int cs = 8; //char size in bits
	int cn = 8; //number of chars to pack per int
	int i = 0; //charcounter 
	int j = 0; //int counter
	int strlen = text.size();
	int patlen = pat.size();
	UltraWord t; //text
	UltraWord p; //pattern
	
	//pack first UW
	unsigned long long int tempblocks[64]={0};
	unsigned long long int temp;
	int shift = 0;
	//tempblocks[0] = 0;
	while(i<strlen & j<UltraWord::NUM_BLOCKS){
		temp = text.at(i);
		shift = cn*cs - ((i%cn)+1)*cs;
		tempblocks[j] = tempblocks[j] | (temp<<shift);
		if((i+1)%cn == 0){
			
			j++;
			//tempblocks[j] = 0;
		}
		i++;
	}	
	std::cout << "i after packing" << i << " \n";
	t.setBlocks(tempblocks);
	//pack pattern into UW. pattern should be shorter than 512 chars
	unsigned long long int tempblocks2[64]={0};
	int k=0; j=0;
	while(k<patlen){
		temp = pat.at(k);
		shift = cn*cs - ((k%cn)+1)*cs;
		std::cout<< "shift: " << shift << "\n";
		tempblocks2[j] = tempblocks2[j] | (temp<<shift);
		if((k+1)%cn == 0){
			
			j++;
			//tempblocks[j] = 0;
		}
		k++;
	}
	p.setBlocks(tempblocks2);
	printUWc(t);
	printUWc(p);
	
	
	//UW window mask
	UltraWord wmask;
	UltraWord one;
	wmask=1;
	one =1;
	for(j=0;j<(patlen*8)-1;j++){
		wmask = (wmask<<1)|one;
	}
	wmask = wmask<<(UltraWord::WORD_SIZE-(patlen*8));
	UltraWord testequal;

	int shcount = strlen - patlen; //number of shifts needed to cover all windows
	int rotcount = strlen - (UltraWord::WORD_SIZE/8); // number of rotations needed to add whole text to UW.
	int count = 0; // number of shifts so far
	std::cout << "shcount" << shcount << " \n";
	std::cout << "rotcount" << rotcount << " \n";
	bool finished = false;
	UltraWord rot;
	while(!finished){
		//std::cout<<"printingyay! \n";
		//printUWc(t);
		testequal = t&wmask;
		testequal = testequal-p;
		if(testequal.iszeros()){
			//match
			res.push_back(count);
		}
		
		if(count<shcount){
			t = t<<8;
			if(count<rotcount){
				rot = text.at(i);
				t = t|rot;
			}
			
		}else{
			finished = true;
		}
		
		
		i++;
		count++;
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
	
	printResults(uwbmh(fst,pattern));

	
	
	return 0;

}
