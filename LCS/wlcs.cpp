#include <cstdio>
#include <string>
#include <stdio.h>
#include <math.h> 
#include <iostream>

//compile = g++ -o wlcs -g wlcs.cpp -std=c++11

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
	int cpw = w/f; //assume divisibility
	X = "*"+X;
	Y = "*"+Y;
	
	unsigned long long int hif = ((1<<f)-1);
	hif=hif<<(w-f);
	printlongbits(hif);
	
	
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
	std::cout<< "k: " <<k << "\n";
	    int l = min(n,k-1) + min(m,k-1) - k + 1;
		int j1 = k-min(m,k-1);
		int j2 = min(n,k);
		int i2 = k-j1;
		int i1 = k-j2;
		int j = j1;
		int i = i2;
		int s = ceil(float(l*f)/float(w));
		std::cout<< "s: " <<s << "\n";
		
		std::cout<< "i: " <<i1 << " - " << i2 << "\n";
		std::cout<< "j: " <<j1 << " - " << j2 << "\n";
		for(int t = 1; t<=s; t++){
			std::cout<< "t: " <<t << "\n";
			
			int ip = max(i1,i-cpw+1);
			int jp = min(j2,j+cpw-1);
			
			std::cout<< "i - ip: " <<i << " - " << ip << "\n";
			std::cout<< "j - jp: " <<j << " - " << jp << "\n";
			//load relevant text and previous diagonals
			unsigned long long int WY = 0;
			unsigned long long int WX = 0;
			unsigned long long int hkm1 = 0;
			unsigned long long int vkm1 = 0;
			int ci = i;
			int cj = j;
			int opbits = 0;
			
			while(ci>=ip & ci>0 & cj<=jp){
				WX = WX<<f | X.at(ci);
				WY = WY<<f | Y.at(cj);
				hkm1 = hkm1<<f | H[ci-1][cj];
				vkm1 = vkm1<<f | V[ci][cj-1];
				ci--;
				cj++;
				opbits++;
			}/*
			std::cout<<"WY: ";
			for(int c=j; c<=jp; c++){
				opbits++;
				WY = WY<<f | Y.at(c);
				std::cout<<Y.at(c);
			}
			std::cout<<"\n";
			std::cout<<"WX: ";
			for(int c=i; c>=ip; c--){
				WX = WX<<f | X.at(c);
				std::cout<<X.at(c);
			}
			std::cout<<"\n";
			//load previous diagonals
			unsigned long long int hkm1 = 0;
			unsigned long long int vkm1 = 0;
			int ci = i; int cj = j;
			while(ci>=ip & cj <=jp){
				if(ci==0){
					hkm1 = hkm1<<f;
					vkm1 = vkm1<<f | V[ci][cj-1];
				}else{
					hkm1 = hkm1<<f | H[ci-1][cj];
					vkm1 = vkm1<<f | V[ci][cj-1];
				}
				ci--;
				cj++;
			}//end while
		
			*/
			unsigned long long int hk = 0;
			unsigned long long int vk = 0;
			
			unsigned long long int WEQ = equals(WX,WY,posmask,f,opbits);
			unsigned long long int W1 = minus(WEQ,vkm1,posmask);
			unsigned long long int W2 = minus(hkm1,vkm1,posmask);
			hk = fieldmax(W1,W2,posmask,f);
			W1 = minus(WEQ,hkm1,posmask);
			W2 = minus(vkm1,hkm1,posmask);
			vk = fieldmax(W1,W2,posmask,f);
			
			/*if(t==1 & k<=m+1){
				vk = vk>>f;
			}*/
			
			
			
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
			ci = i;
			cj = j;
			while(ci>=ip & ci>0 & cj<=jp){
			H[ci][cj] = (hk&hif)>>w-f; 
			hk = hk<<f;
			V[ci][cj] = (vk&hif)>>w-f; 
			vk = vk<<f;
			ci--;
			cj++;
		}
			/*
			while(ci>=ip & ci>0 & cj<=jp){
			
			
			ci = ip; cj = jp;
			while(ci<=i & cj >=j){
				H[ci][cj] = hk&((1<<f)-1);
				hk=hk>>f;
				ci++;
				cj--;
			}
			
			if(t==1){
				
				ci = ip; cj = jp;
				if(ci==0){
					ci++;cj--;
				}
				while(cj>=max(0,k-m)){
					//std::cout<< "ci: " <<ci << "\n";
					//std::cout<< "cj: " <<cj << "\n";
		
					V[ci][cj] = vk&((1<<f)-1);
					vk=vk>>f;
					ci++;
					cj--;
				}
			}else{
				ci = ip; cj = jp;
				while(ci<=i & cj >=j){
					V[ci][cj] = vk&((1<<f)-1);
					vk=vk>>f;
					ci++;
					cj--;
				}
			}
			*/
			std::cout<<"H: \n";
			printmatrix(H,m+1,n+1);
			std::cout<<"V: \n";
			printmatrix(V,m+1,n+1);
			
			std::cout << "*****************************************\n";
			
			i = ip-1;
			j = jp+1;
		}//end t loop
	}//end k loop
	
	
	for(int c = 0; c<n; c++){
		length = length + H[m][c];
	}
	for(int i = 0; i<m; i++){
		free(V[i]);
		free(H[i]);
	}
	free(H);
	free(V);
	return length;
}

int main(){
	//std::string y = "aabbba";
	//std::string x = "abbab";
	
	//std::string y = "abbarb";
	//std::string x = "abcdefabcac";
	
	std::string y = "agwgwtawbw";
	std::string x = "gxtxxayxbxy";
	
	
	int retlength = swlcs(x,y,x.size(),y.size());
	std::cout<<"LENGTH: "<<retlength<<"\n";
}