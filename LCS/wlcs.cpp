#include <cstdio>
#include <string>
#include <stdio.h>
#include <math.h> 
#include <iostream>

//compile = g++ -o wlcs -g wlcs.cpp -std=c++11
//for a regular word of 64 bits
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




int lcslength(std::string X, std::string Y, int m, int n){
	int w = 64; //block size, not UW.
	//std::string X = "*";
	//std::string Y = "*";
	//X.append(x);
	//Y.append(y);
	//static const int m = X.size();
	//static const int n = Y.size();
	X = "*"+X;
	Y = "*"+Y;
	std::cout<<"X: "<<X<<"\n";
	std::cout<<"Y: "<<Y<<"\n";
	std::cout<<"m: "<<m<<"\n";
	std::cout<<"n: "<<n<<"\n";
	//using ascii, 7 bits for now
	int f = 7 + 1; //field size. 8th bit is a test bit, assume that w%f = 0 always.
	int c; //general counter
	//masks needed
	unsigned long long int posmask = 1<<(f-1);
	for(c=1; c<=(w/f)-1; c++){
		posmask = posmask<<f | posmask;
	}
	unsigned long long int negmask = ~posmask;
	printlongbits(posmask);
	printlongbits(negmask);
	
	//int H [m+1][n+1] ;
	int** H = (int**)calloc(m+1,sizeof(int*));
	int** V = (int**)calloc(m+1,sizeof(int*));
	for(int i = 0; i<m+1; i++){
		H[i] = (int*)calloc(n+1,sizeof(int));
		V[i] = (int*)calloc(n+1,sizeof(int));
	}
	std::cout<<"H:\n";
			for(int o = 0; o<m+1; o++){
				for(int p = 0;p<n+1; p++){
					std::cout<<H[o][p]<< " ";
				}
				std::cout<<"\n";
			}
	//int V [m+1][n+1];
	//H = {0};
	//V = {0};
	
	H[0][1] = 0;
	V[1][0] = 0;
	int cpw = w/f;
	std::cout<<"cpw: "<<cpw<<"\n";
	int length = 0;
	int k; //diagonal counter
	for(k=2;k<=(m+n);k++){
		std::cout<<"k: "<<k<<"\n";
		//length of the diagonal
		int l = min(n,k-1) + min(m,k-1) - k + 1;
		// std::cout<<"l: "<<l<<"\n";
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
		//std::cout<<"s: "<<s<<"\n";
		for(t=1;t<=s;t++){
			//int jp = min(j+s-1,j2);
			int jp = min(j2,t*cpw);
			//int ip = max(i+s-1,i1);
			int ip = max(i1,i2-(t*cpw));
			std::cout<<"t: "<<t<<"\n";
			 std::cout<<"i: "<<i<<"\n";
			 std::cout<<"ip: "<<ip<<"\n";
			std::cout<<"j: "<<j<<"\n";
			std::cout<<"jp: "<<jp<<"\n";
			  
			 
			  
			long long int wy=0;
			long long int wx=0;
			//pack wy 
			//int i =1;
			std::cout<<"\n wy: ";
			//std::cout<<Y.at(c-1)<<"\n";
			for(c =j; c<=jp; c++){
				wy = wy<<f | Y.at(c);
				std::cout<<Y.at(c);
				//i++;
			}
			std::cout<<"\n";
			printlongbits(wy); 
			//pack wx (reverse order)
			std::cout<<"\n wx: ";
			//std::cout<<X.at(c-1)<<"\n";
			for(c = i; c>=ip; c--){
				wx = wx<<f | X.at(c);
				std::cout<<X.at(c);
			}
			   std::cout<<"\n";
			//std::cout<<"\n wx: ";
			printlongbits(wx); 
			unsigned long long int hkm1 = 0; // H horizontal k-1
			unsigned long long int vkm1 = 0; // V horizontal k-1
			int ic = i-1;
			int jc = j; //counters
			//load diagonal k-1
			std::cout<<"loading diagonal Hkm1\n";
			while(ic>= ip-1 & jc<=jp){
				std::cout<<"ic: "<<ic<<"\n";
				std::cout<<"jc: "<<jc<<"\n";
				if(ic!=-1){
					hkm1 = hkm1<<f | H[ic][jc];
				}else{
					hkm1 = hkm1<<f;
				}
				ic--;
				jc++;
			}
			ic = i; 
			jc = j-1;
			while(ic>= ip & jc<=jp-1){
				vkm1 = vkm1<<f | V[ic][jc];
				ic--;
				jc++;
			}
			
			unsigned long long int weq = equals(wx,wy,posmask,f);
			std::cout<<"equals: \n";
			printlongbits(weq);
			
			unsigned long long int w1 = weq-vkm1;
			unsigned long long int w2 = hkm1-vkm1;
			//hk = max(w1,w2,0)
			unsigned long long int hk = fieldmax(w1,w2,posmask,f);
			//hk = fieldmax(hk,0,posmask,f);
			
			w1 = weq - hkm1;
			w2 = vkm1 - hkm1;
			unsigned long long int vk = fieldmax(w1,w2,posmask,f);
			//vk = fieldmax(vk,0,posmask,f);
			
			//load packed words into matrix
			for(int o = ip; o<=i; o++){
				for(int p = jp; p>=j; j--){
					H[o][p] = hk&((1<<f)-1);
					hk>>f;
					V[o][p] = vk&((1<<f)-1);
					vk>>f;
				}
			}
			
			//PRINT MATRIX TO SEE IF IT WORKS. H, then V
			std::cout<<"H:\n";
			for(int o = 0; o<m; o++){
				for(int p = 0;p<n; p++){
					std::cout<<H[o][p]<< " ";
				}
				std::cout<<"\n";
			}
			std::cout<<"\n";
			std::cout<<"V:\n";
			for(int o = 0; o<m; o++){
				for(int p = 0;p<n; p++){
					std::cout<<V[o][p]<< " ";
				}
				std::cout<<"\n";
			}
			i = ip+1;
			j = jp+1;
		}
	}
	for(int i = 0; i<n; i++){
		free(V[i]);
		free(H[i]);
	}
	free(H);
	free(V);
	return length;
	
}

int main(){
	std::string y = "abba";
	std::string x = "abacaba";
	
	int retlength = lcslength(x,y,x.size(),y.size());
}
