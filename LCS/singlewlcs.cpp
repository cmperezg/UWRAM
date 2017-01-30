#include <cstdio>
#include <string>
#include <stdio.h>
#include <math.h> 
#include <iostream>

//compile = g++ -o singlewlcs -g singlewlcs.cpp -std=c++11

//test where all diagonals fit in a single word
// w = 64 = 8 chars

void printlongbits(unsigned long long int n){
	long long int i;
	for(i=64-1;i>=0;i--){
		unsigned long long int mask = ((unsigned long long int)1)<<i;
		unsigned long long int maskedn = n&mask;
		unsigned long long int thebit = maskedn >> i;
		printf("%u",(unsigned int)thebit);
		if(i%8==0){
			printf(" ");
		}
	}
	printf("\n");
}


int min(int a, int b){
	return !(b<a)?a:b; 
}

int max(int a, int b){
	return (b<a)?a:b; 
}

//fieldwise max for two words
unsigned long long int equals(unsigned long long int wx,unsigned long long int wy,unsigned long long int posmask, int f){
	unsigned long long negmask = ~posmask;
	wx = wx | posmask;
	unsigned long long int sub = wx-wy;
	sub = sub&posmask;
	wx = wx&negmask;
	unsigned long long int mx = 0;
	int i;
	for(i=0;i<f;i++){
		mx = mx|(mx>>1);
	}
	unsigned long long int my = ~mx;
	
	return (wx&mx)|(wy&my);
	
}
//equals function. Substract wy from wx,mask out non-zero results and
//write a 1 in each field that resulted in zero.
unsigned long long int fieldmax(unsigned long long int wx,unsigned long long int wy,unsigned long long int posmask, int f){
	unsigned long long int negmask = ~posmask;
	wx = wx | posmask;
	unsigned long long int ans = wx-wy;
	ans = ans&posmask;
	
	//ans now holds a 1 at the test bit of every field where wx>=wy.
	//now repeat the other way around and & results to keep only fields which are equal.
	wx = wx&negmask;
	wy = wy|posmask;
	unsigned long long int temp = wy-wx;
	temp = temp&posmask;
	
	ans = ans&temp;
	
	ans = ans>>f-1;
	return ans;
}


int main(){
	std::string y = "abba";
	std::string x = "abacaba";
	
	int retlength = swlcs(x,y,x.size(),y.size());
}