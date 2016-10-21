#include <cstdio>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <nmmintrin.h> // intel SSE4.2 instructions

//g++ -g sse4test.cpp -o sse4test -std=c++11 -msse4.2

//test to call sse4.2 functions (pcmpestrm)

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
	printf(" ");
}


void print128_ch(__m128i var){
	
    uint8_t *val = (uint8_t*) &var;
    printf("Text: %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c \n", 
           val[0], val[1], val[2], val[3], val[4], val[5], 
           val[6], val[7], val[8], val[9], val[10], val[11],
           val[12], val[13], val[14], val[15]);
}

void print128_num(__m128i var){
	
    uint8_t *val = (uint8_t*) &var;
    printf("Text: %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i \n", 
           val[0], val[1], val[2], val[3], val[4], val[5], 
           val[6], val[7], val[8], val[9], val[10], val[11],
           val[12], val[13], val[14], val[15]);
}

void print128_bits(__m128i var){
	uint32_t *val = (uint32_t*) &var;
	printbits(var[0]);
	printbits(var[1]);
	printbits(var[2]);
	printbits(var[3]);
	printf("\n");
}

int main(){
	std::string a = "abab";
	std::string pa = "ab";
	//characters are stored in INVERSE order as the function! 
	//__m128i s = _mm_set_epi8('i',' ','a','m',' ','a','n',' ','a','n','t','e','l','o','p','e');
	__m128i s = _mm_set_epi8('e','p','o','l','e','t','n','a',' ','n','a',' ','m','a',' ','i');
	__m128i p = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,'t','n','a');
	
	//__m128i s = _mm_set_epi8(0,0,0,0,0,0,0,0,'a','n','a','n','a','n','a','b');
	//__m128i p = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,0,'a','n');
	
	print128_num(s);
	print128_num(p);
	
	print128_bits(s);
	print128_bits(p);
	__m128i res =  _mm_cmpistrm(s, p, 0);
	
	print128_bits(res);
	
	
	//int resi = _mm_cmpistri(s, p, 0);
	//print128_num(res);
	//printf("cmpistri: %u\n",resi);
	
	return 0;
}
