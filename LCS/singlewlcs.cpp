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


unsigned long long int equals(unsigned long long int wx,unsigned long long int wy,unsigned long long int posmask,int f,int active){	
	unsigned long long negmask = ~posmask;
	wx = wx | posmask;
	unsigned long long int sub = wx-wy;
	sub = sub&posmask;
	wx = wx&negmask;
	wy = wy|posmask;
	unsigned long long int sub2 = wy - wx;
	sub2 = 	sub2&posmask;
	unsigned long long int activemask = (1<<f)-1;
	for(int i=0;i<active-1;i++){
		activemask = activemask | activemask<<f;
	}
	printlongbits(activemask);
	return ((sub&sub2)>>(f-1))&activemask;
	
}
//fieldwise subtraction x-y
unsigned long long int minus(unsigned long long int x, unsigned long long int y, unsigned long long int posmask){
	x = x|posmask;
	return x-y;
	
}
//fieldwise max(x,y,0)
unsigned long long int fieldmax(unsigned long long int x,unsigned long long int y,unsigned long long int posmask, int f){
	unsigned long long int negmask = ~posmask;
	unsigned long long int mx = x&posmask;
	unsigned long long int my = y&posmask;
	for(int i =0; i<f-1;i++){
		mx = mx | mx>>1;
		my = my | my>>1;
	}
	/*
	std::cout<<"FIELDWISE:  \n";
	std::cout<<"x: ";
	printlongbits(x);
	std::cout<<"mx: ";
	printlongbits(mx);
	std::cout<<"y: ";
	printlongbits(y);
	std::cout<<"my: ";
	printlongbits(my);
	std::cout<<"an: ";
	printlongbits(((mx&x)&negmask) | ((my&y)&negmask));
	*/
	
	return ((mx&x)&negmask) | ((my&y)&negmask);
}

void printmatrix(int** T, int m, int n){
	
	for(int i = 0; i<m; i++){
		for(int j = 0; j<n; j++){
			std::cout<< T[i][j] << " ";
		}
		std::cout<< "\n";
	}
}

int swlcs(std::string X, std::string Y, int m, int n){
	int w = 64;
	int f = 7+1; //ascii alphabet
	int cpw = w/f;
	unsigned long long int hif = ((1<<f)-1);
	hif=hif<<(w-f);
	printlongbits(hif);
	
	X = "*"+X;
	Y = "*"+Y;
	
	unsigned long long int posmask = 1<<(f-1);
	for(int c=1; c<=(w/f)-1; c++){
		posmask = posmask<<f | posmask;
	}
	
	int** H = (int**)calloc(m+1,sizeof(int*));
	int** V = (int**)calloc(m+1,sizeof(int*));
	for(int i = 0; i<m+1; i++){
		H[i] = (int*)calloc(n+1,sizeof(int));
		V[i] = (int*)calloc(n+1,sizeof(int));
	}
	
	H[0][1] = 0;
	V[1][0] = 0;
	
	int length = 0; //length of the lcs
	for(int k =2; k<= m+n; k++){//loop through diagonals
		std::cout<<"k: " << k << "\n";
		int l = min(n,k-1) + min(m,k-1) - k + 1;
		std::cout << "l: " << l << "\n";
		int j1 = k-min(m,k-1);
		int j2 = min(n,k);
		int i2 = k-j1;
		int i1 = k-j2;
		
		std::cout<< "i: " <<i1 << " - " << i2 << "\n";
		std::cout<< "j: " <<j1 << " - " << j2 << "\n";
		
		//load relevant text and previous diagonals
		unsigned long long int WY = 0;
		unsigned long long int WX = 0;
		unsigned long long int hkm1 = 0;
		unsigned long long int vkm1 = 0;
		int ci = i2;
		int cj = j1;
		int opbits = 0;
		
		while(ci>=i1 & ci>0 & cj<=j2){
			WX = WX<<f | X.at(ci);
			WY = WY<<f | Y.at(cj);
			hkm1 = hkm1<<f | H[ci-1][cj];
			vkm1 = vkm1<<f | V[ci][cj-1];
			ci--;
			cj++;
			opbits++;
		}

		unsigned long long int hk = 0;
		unsigned long long int vk = 0;
		
		unsigned long long int WEQ = equals(WX,WY,posmask,f,opbits);
		unsigned long long int W1 = minus(WEQ,vkm1,posmask);
		unsigned long long int W2 = minus(hkm1,vkm1,posmask);
		hk = fieldmax(W1,W2,posmask,f);
		W1 = minus(WEQ,hkm1,posmask);
		W2 = minus(vkm1,hkm1,posmask);
		vk = fieldmax(W1,W2,posmask,f);

		std::cout<<"WY: ";
		printlongbits(WY);
		std::cout<<"WX: ";
		printlongbits(WX);
		std::cout<<"WEQ: ";
		printlongbits(WEQ);
		std::cout<<"hkm1: ";
		printlongbits(hkm1);
		std::cout<<"vkm1: ";
		printlongbits(vkm1);
		std::cout<<"hk: ";
		printlongbits(hk);
		std::cout<<"vk: ";
		printlongbits(vk);
		
		int aux = (w-(opbits*f));
		hk = hk<<aux;
		vk = vk<<aux;
		std::cout<<"hk: ";
		printlongbits(hk);
		std::cout<<"vk: ";
		printlongbits(vk);
		
		
		//set diagonals
		
		ci = i2;
		cj = j1;
		while(ci>=i1 & ci>0 & cj<=j2){
			H[ci][cj] = (hk&hif)>>w-f; 
			hk = hk<<f;
			V[ci][cj] = (vk&hif)>>w-f; 
			vk = vk<<f;
			ci--;
			cj++;
		}

		std::cout<<"H: \n";
		printmatrix(H,m+1,n+1);
		std::cout<<"V: \n";
		printmatrix(V,m+1,n+1);
		
		std::cout << "*****************************************\n";
	}
	for(int c = 0; c<n; c++){
		length = length + H[m][c];
	}
	for(int i = 0; i<m+1; i++){
		free(V[i]);
		free(H[i]);
	}
	free(H);
	free(V);
	return length;
}

int main(){
	std::string y = "aabbba";
	std::string x = "abbab";
	//std::string y = "abbarb";
	//std::string x = "abcdefabcac";
	int retlength = swlcs(x,y,x.size(),y.size());
	std::cout<<"LENGTH: "<<retlength<<"\n";
}