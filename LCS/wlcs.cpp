#include <cstdio>
#include <string>
#include <stdio.h>
#include <math.h> 
#include <iostream>

//compile = g++ -o wlcs -g wlcs.cpp -std=c++11
//for a regular word of 64 bits

int min(int a, int b){
	return !(b<a)?a:b; 
}
int max(int a, int b){
	return (b<a)?a:b; 
}

/* function to print the bits of an int */
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
int lcslength(std::string X, std::string Y){
	int w = 64; //block size, not UW.
	int m = X.size();
	int n = Y.size();
	
	//using ascii, 7 bits for now
	int f = 7 + 1; //field size. 8th bit is a test bit, assume that w%f = 0 always.
	int c; //general counter
	//masks needed
	unsigned long long int posmask = 1<<(f-1);
	for(c=1; c<=(w/f)-1; c++){
		posmask = posmask<<f | posmask;
	}
	unsigned long long int negmask = ~posmask;
	//printlongbits(posmask);
	//printlongbits(negmask);
	
	int H [m][n];
	int V [m][n];
	
	H[0][1] = 0;
	V[1][0] = 0;
	
	int length = 0;
	int k; //diagonal counter
	for(k=2;k<=(m+n);k++){
		//length of the diagonal
		int l = min(n,k-1) + min(m,k-1) - k + 1;
		//relevant substring index for Y
		int j1 = k - min(m,k-1);
		int j2 = min(n,k);
		//relevant substring index for X
		int i2 = k-j1;
		int i1 = k-j2;
		
		int j = j1;
		int i = i2;
		int s = ceil(double(l*f)/double(w)); //words needed to load diagonal
		int t;
		for(t=1;t<=s;t++){
			int jp = min(j+s-1,j2);
			int ip = max(i+s-1,i1);
			  
			long long int wy;
			long long int wx;
			//pack wy 
			int i =1;
			for(c =j; c<=jp; c++){
				int sh = w-i*f;
				wy = wy | Y.at(c-1)<<sh;
				std::cout<<Y.at(c-1);
				i++;
			}
			std::cout<<"\n wy: ";
			printlongbits(wy);                                                    
			
		}
	}
	
	return length;
	
}

int main(){
	std::string y = "abba";
	std::string x = "abacaba";
	
	int retlength = lcslength(x,y);
}
