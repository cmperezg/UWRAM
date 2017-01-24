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

//equals function. Substract wy from wx,mask out non-zero results and
//write a 1 in each field that resulted in zero.
unsigned long long int equals(unsigned long long int wx,unsigned long long int wy,unsigned long long int posmask, int f){
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




int lcslength(std::string X, std::string Y){
	int w = 64; //block size, not UW.
	//std::string X = "*";
	//std::string Y = "*";
	//X.append(x);
	//Y.append(y);
	int m = X.size();
	int n = Y.size();
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
	
	int H [m+1][n+1];
	int V [m+1][n+1];
	
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
			while(ic>= ip-1 & jc<=jp){
				hkm1 = hkm1<<f | H[ic][jc];
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
			
			                                                
			i = ip+1;
			j = jp+1;
		}
	}
	
	return length;
	
}

int main(){
	std::string y = "abba";
	std::string x = "abacaba";
	
	int retlength = lcslength(x,y);
}
