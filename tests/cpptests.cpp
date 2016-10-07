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

int SIZE_OF_INT = 8;  //long long int for this test
int SIZE_OF_BYTE = 8;
int NUM_BLOCKS = 64;
int BLOCK_SIZE = SIZE_OF_INT * SIZE_OF_BYTE;
int WORD_SIZE = BLOCK_SIZE * NUM_BLOCKS;


/* function to print the bits of an int */
void printbits(unsigned long long int n){
	long long int i;
	for(i=SIZE_OF_INT*SIZE_OF_BYTE-1;i>=0;i--){
		unsigned long long int mask = ((unsigned long long int)1)<<i;
		unsigned long long int maskedn = n&mask;
		unsigned long long int thebit = maskedn >> i;
		printf("%u",(unsigned int)thebit);
		//printf("%llu",n);
	}
	//printf("%llu",n);
	printf("\n");
}

int[] packText(string s){
	long long int strlen = s.size();
	
	int cs = 8; //char size in bits
	int cn = 4; //number of chars to pack per int
	
	int intsnec = ceil(strlen/cn);
	unsigned int packed[intsnec];
	bool finished = false;
	int i = 0; //charcounter
	int j = 0; //int counter
	while(!finished){
	}
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
	
	printf("size of char: %lu \n",sizeof(char));
	printf("size of 'a': %lu \n",sizeof('a'));
	printf("size of abcd: %lu \n", sizeof("abcd"));
	
	
	//text tests
	
	ifstream infile {"lidata10.txt"};
	string fst{istreambuf_iterator<char>(infile),istreambuf_iterator<char>()};
	
	transform(fst.begin(),fst.end(),fst.begin(),::tolower);
	
	
	
	return 0;
}
