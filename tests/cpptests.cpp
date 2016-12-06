#include <cstdio>
#include <vector>
#include <chrono>
#include <tuple>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include "ultraword.h"

//compile: g++ cpptests.cpp ultraword.cpp -o cpptests -std=c++11
//using namespace std::string;
//using namespace std::vector;

int SIZE_OF_INT = 8;  //long long int for this test
int SIZE_OF_BYTE = 8;
int NUM_BLOCKS = 64;
int BLOCK_SIZE = SIZE_OF_INT * SIZE_OF_BYTE;
int WORD_SIZE = BLOCK_SIZE * NUM_BLOCKS;



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



/* function to print the bits of an int */
void printlongbits(unsigned long long int n){
	long long int i;
	for(i=SIZE_OF_INT*SIZE_OF_BYTE-1;i>=0;i--){
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

void printbits(unsigned int n){
	int i;
	//sizeof int 32 bits.
	for(i=32-1;i>=0;i--){
		unsigned int mask = ((unsigned int)1)<<i;
		unsigned int maskedn = n&mask;
		unsigned int thebit = maskedn >> i;
		printf("%u",(unsigned int)thebit);
		if(i%8==0){
			printf(" ");
		}
	}
	printf("\n");
}

//print packed text
void print(std::vector<unsigned int> & v){
	printf("PACKED TEXT: \n");
	int i;
	int x = v.size();
	for(i=0;i<x;i++){
		printbits(v.at(i));
	}
}

void print64(std::vector<unsigned long long int> & v){
	printf("PACKED TEXT: \n");
	int i;
	int x = v.size();
	for(i=0;i<x;i++){
		printlongbits(v.at(i));
	}
}

std::vector<unsigned int> packText32(std::string s){
	long long int strlen = s.size();

	int cs = 8; //char size in bits
	int cn = 4; //number of chars to pack per int

	int intsnec = ceil((float)strlen/(float)cn);
	std::vector<unsigned int> packed(intsnec,0);

	bool finished = false;
	int i = 0; //charcounter
	int j = 0; //int counter
	int shift = 0;
	unsigned int temp;
	while(!finished){
		temp = s.at(i);
		shift = cn*cs - ((i%cn)+1)*cs;
		packed.at(j) = packed.at(j) | (temp<<shift);
		if((i+1)%cn == 0){
			j++;
		}
		i++;
		if(i>=strlen){
			finished = true;
		}

	}
	return packed;
}

std::vector<unsigned long long int> packText64(std::string s){
	long long int strlen = s.size();

	int cs = 8; //char size in bits
	int cn = 8; //number of chars to pack per int

	int intsnec = ceil((float)strlen/(float)cn);
	std::vector<unsigned long long int> packed(intsnec,0);

	bool finished = false;
	int i = 0; //charcounter
	int j = 0; //int counter
	int shift = 0;
	unsigned long long int temp;
	while(!finished){
		temp = s.at(i);
		shift = cn*cs - ((i%cn)+1)*cs;
		packed.at(j) = packed.at(j) | (temp<<shift);
		if((i+1)%cn == 0){
			j++;
		}
		i++;
		if(i>=strlen){
			finished = true;
		}

	}
	return packed;
}

std::vector<UltraWord> packTextUW(std::string s){
	long long int strlen = s.size();
	printf("strlen: %lld\n",strlen);
	int cs = 8; //char size in bits
	long long int textsize = strlen*cs;
	int wn = ceil((float)textsize/(float)UltraWord::WORD_SIZE);
	//printf("wordsneeded: %d\n",wordsneeded);
	printf("wordsize: %d\n",UltraWord::WORD_SIZE);
	int cn = UltraWord::WORD_SIZE/cs; //number of chars to pack per word
	printf("cn: %d\n",cn);

	int intsnec = ceil((float)(strlen*8)/(float)cn);
	printf("intsnec: %d\n",intsnec);
	//int wn = ceil((float)intsnec/(float)UltraWord::NUM_BLOCKS);
	printf("wordsneeded: %d\n",wn);
	std::vector<UltraWord> packed(wn);
	printf("packed vector size: %d\n",(int)packed.size());
	bool finished = false;
	int i = 0; //charcounter
	int j = 0; //int counter
	int shift = 0;
	UltraWord temp;
	while(!finished){
		//printf("whydoesitfail :( i: %d , j: %d \n",i,j);
		temp = s.at(i);
		shift = cn*cs - ((i%cn)+1)*cs;
		packed.at(j) = packed.at(j) | (temp<<shift);
		if((i+1)%cn == 0){
			j++;
		}
		i++;
		if(i>=strlen){
			finished = true;
		}

	}
	return packed;
}

int main(){
	/*
	int l = sizeof(long long int);
	printf("size of long long int: %d \n",l);

	unsigned long long int t = ((unsigned long long int)1)<<64;
	printf("size of long long int: %llu \n",t);
	printbits(t);
	*/

	//std::vector<std::vector<UltraWord>> table(10, std::vector<UltraWord>(4));
	/*
	printf("size of char: %lu \n",sizeof(char));
	printf("size of '8': %lu \n",sizeof('8'));
	printf("intrep of '8': %d \n",'8');
	printf("size of abcd: %lu \n", sizeof("abcd"));
	*/

	//text tests

	std::ifstream infile {"lidata10.txt"};
	std::string fst{std::istreambuf_iterator<char>(infile),std::istreambuf_iterator<char>()};

	std::transform(fst.begin(),fst.end(),fst.begin(),::tolower);

	int i;

	std::string smtest = "abcde";
	//vector<int> shifted(20);
	//printf("size of smtest: %lu \n", sizeof(smtest));
	//printf("size of 20 int vector: %lu \n", sizeof(shifted));
	//vector<unsigned int> res = packText(smtest);
	//std::vector<unsigned long long int> res = packText64(fst);
	////print64(res);
	std::cout<<"a - b: "<<  'a'-'a'<< "\n";
	//UW PACK TEST
	/*
	std::vector<UltraWord> res = packTextUW(fst);
	for(i=0;i<res.size();i++){
		res.at(i).print();
	}*/

	std::cout << "UW shift test \n";	
	UltraWord p;
	std::string pat = "vestibulum";
	int patlen = pat.size();
	int j = 0;
	int k = 0;
	int cs = 8; //char size in bits
	int cn = 8; //number of chars to pack per int
	unsigned long long int temp;
	unsigned long long int tempblocks2[64]={0};
	int shift = 0;
	while(k<patlen){
		temp = pat.at(k);
		shift = cn*cs - ((k%cn)+1)*cs;
		tempblocks2[j] = tempblocks2[j] | (temp<<shift);
		if((k+1)%cn == 0){	
			j++;
		}
		k++;
	}
	p.setBlocks(tempblocks2);
	printUWc(p);
	//p.print();
	p = p>>64;
	printUWc(p);
	return 0;
}
