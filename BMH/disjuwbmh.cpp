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


//compile: g++ disjuwbmh.cpp ultraword.cpp -o disjuwbmh -std=c++11

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
	for(i=8*8-1;i>=0;i--){
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
	int tempoffset = 0;
	
	//PREPROCESSING
	//pack first UW
	unsigned long long int tempblocks[64]={0};
	unsigned long long int temp;
	int shift = 0;
	while(i<strlen & j<UltraWord::NUM_BLOCKS){
		temp = text.at(i);
		shift = cn*cs - ((i%cn)+1)*cs;
		tempblocks[j] = tempblocks[j] | (temp<<shift);
		if((i+1)%cn == 0){	
			j++;
		}
		i++;
		tempoffset++;
	}	

	t.setBlocks(tempblocks);
	//printUWc(t);
	//pack pattern into UW. pattern should be shorter than 512 chars
	unsigned long long int tempblocks2[64]={0};
	int k=0; j=0;
	//how many blocks does the pattern need?
	int bn = ceil((float)patlen/(float)cn);
	//how many times will the pattern fit?
	int ft = floor((float)UltraWord::NUM_BLOCKS/(float)bn);
	//pack first
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
	//replicate pattern ft times over p
	for(k=0;k<ft;k++){
		p = p | (p>>(bn*cs*cn));
	}
	

	
	//SEARCH
	
	bool finished = false;
	UltraWord sub;
	int check = UltraWord::NUM_BLOCKS - (UltraWord::NUM_BLOCKS%bn) -1; //last useful block
	int shifts = (bn*cn)-1;
	int align = (cn-(patlen%cn))*cs;
	int l; 
	int offset = 0;
	while(!finished){ // while there is still more text
		if(i>= strlen){
			finished = true;
		}
		int shiftcount;
		//while there is more to search in current word
		for(shiftcount=0;shiftcount<=shifts;shiftcount++){ 
			sub = t - p;
			while(check>=0){

				if((sub.blocks[check]>>align) == 0){	
					//check the rest of the block used
					for(l=1;l<bn;l++){
						if(sub.blocks[check-l]!=0){
							break;
						}else{
							if(l==bn-1){
								//pattern found
								/*std::cout<<"FOUND" << "\n";
								std::cout<<"index: " << offset+shiftcount+((check-l)*cn) << "\n";
								std::cout<<"offset: " << offset << "\n";
								std::cout<<"shiftcount: " << shiftcount << "\n";
								std::cout<<"check: " << check << "\n";
								std::cout<<"l: " << l << "\n\n\n";*/
								res.push_back(offset+shiftcount+((check-l)*cn));
							}
						}
					}
					
				}
				check = check - bn;
			}
			t = t<<cs;
			check = UltraWord::NUM_BLOCKS - (UltraWord::NUM_BLOCKS%bn) -1;
		}
		if(finished){
			break;
		}
		//pack next UW
		unsigned long long int tb[64]={0};
		int shift = 0;
		j=0;
		offset = tempoffset;
		//tempoffset = 0;
		while(i<strlen & j<UltraWord::NUM_BLOCKS){
			tempoffset++;
			temp = text.at(i);
			shift = cn*cs - ((i%cn)+1)*cs;
			tb[j] = tb[j] | (temp<<shift);
			if((i+1)%cn == 0){	
				j++;
			}
			i++;
			
		}
		t.setBlocks(tb);

	}
	std::cout<<"strlen: " << strlen << "\n";
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
	std::list<int> s = uwbmh(fst,pattern);
	s.sort();
	printResults(s);

	
	
	return 0;

}
