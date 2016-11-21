#include <cstdio>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <list>

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