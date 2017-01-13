#include <cstdio>
#include <string>
#include <stdio.h>
#include <math.h> 

//compile = g++ -o wlcs -g lcs.cpp -std=c++11
//for a regular word of 64 bits

int min(int a, int b){
	return !(b<a)?a:b; 
}
int max(int a, int b){
	return (b<a)?a:b; 
}

int lcslength(std::string X, std::string Y){
	int w = 64; //block size, not UW.
	int m = X.size();
	int n = Y.size();
	
	//using ascii, 7 bits for now
	int f = 7 + 1; //field size. 8th bit is a test bit
	
	int H [m][n];
	int V [m][n];
	
	H[0][1] = 0;
	V[1][0] = 0;
	
	int length = 0;
	int k; //diagonal counter
	for(k=2;k<=(m+n);k++){
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
			
			                                                    
			
		}
	}
	
	return length;
	
}
