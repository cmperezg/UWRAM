#include <cstdio>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <nmmintrin.h> // intel SSE4.2 instructions

//g++ -g sse4test.cpp -o sse4test -std=c++11 -msse4.2

//test to call sse4.2 functions (pcmpestrm)


void printbits(char n){
	int i;
	//sizeof int 32 bits.
	for(i=8-1;i>=0;i--){
		unsigned int mask = ((unsigned int)1)<<i;
		unsigned int maskedn = n&mask;
		unsigned int thebit = maskedn >> i;
		printf("%u",(unsigned int)thebit);
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
	uint8_t *val = (uint8_t*) &var;
	printbits(val[0]);
	printbits(val[1]);
	printbits(val[2]);
	printbits(val[3]);
	printbits(val[4]);
	printbits(val[5]);
    printbits(val[6]);
    printbits(val[7]);
    printbits(val[8]);
    printbits(val[9]);
    printbits(val[10]);
    printbits(val[11]);
    printbits(val[12]);
    printbits(val[13]);
    printbits(val[14]);
    printbits(val[15]);
	printf("\n");
}

__m128i pcmpestrm(const char *p1, const char *p2){

	__m128i smm1 = _mm_loadu_si128 ((__m128i *) p1);
	__m128i smm2 = _mm_loadu_si128 ((__m128i *) p2);
	print128_ch(smm1);
	print128_ch(smm2);
	print128_bits(smm1);
	print128_bits(smm2);
	//return  _mm_cmpestrm(smm1,13, smm2,2, 12);
	//return  _mm_cmpestrm(smm1,15, smm2,2, _SIDD_UBYTE_OPS|_SIDD_CMP_EQUAL_ORDERED|_SIDD_BIT_MASK);
	//return  _mm_cmpestrm(smm2,2, smm1,15, _SIDD_UBYTE_OPS|_SIDD_CMP_EQUAL_ORDERED|_SIDD_UNIT_MASK);
	return  _mm_cmpistrm(smm2, smm1, _SIDD_UBYTE_OPS|_SIDD_CMP_EQUAL_ORDERED|_SIDD_UNIT_MASK);

}

/*int _STTNI_strcmp (const char *p1, const char *p2) {
	const int mode = 76;
	__m128i smm1 = _mm_loadu_si128 ((__m128i *) p1);
	__m128i smm2 = _mm_loadu_si128 ((__m128i *) p2);
	int ResultIndex;
	while (1) {
	ResultIndex = _mm_cmpistri (smm1, smm2, mode );
	if (ResultIndex != 16) { break; }
	p1 = p1+16;
	p2 = p2+16;
	smm1 = _mm_loadu_si128 ((__m128i *)p1);
smm2 = _mm_loadu_si128 ((__m128i *)p2);
}
p1 = (char *) & smm1;
p2 = (char *) & smm2;
if(p1[ResultIndex]<p2[ResultIndex]) return ‐1;
if(p1[ResultIndex]>p2[ResultIndex]) return 1;
03/25/2011
return 0;
}
*/
char compare(int i, int j, std::string a){
	if(a[i]<a[j]) return '<';
	else if(a[i]>a[j]) return '>';
	return '=';
}

int max_suffix_duval(std::string a, int r0, int n) {
    // Inputs integers r0 and n with 0 <= r0 <= n and a string a[r0..n].
    // Returns the integer r with r0 <= r <= n such that a[r..n] is the
    // maximum suffix of a[r0..n]. compare(i, j, a) must compare a[i]
    // and a[j] and return '<', '=' or '>' accordingly.
    int r = r0, s = r + 1, m = 1, d;
    int *M = new int[n + 2];
    M[1] = 1;
    while (s <= n)
        switch (compare(s, s - m, a)) {
            case '<': m = (++s) - r; M[m] = m; break;
            case '=': M[(++s) - r] = m; break;
            case '>':
                d = (s - r) % m;
                if (d > 0) {
                    r = s - d;
                    m = M[d];
                } else {
                    r = s++;
                    m = 1;
                }
        }
    delete M;
    return r;
}

int main(){
	//const char *s = "they helped her";
	//const char *p = "he";

	const char *s = "na a bananana na";
	const char *p = "nana";

	__m128i res = pcmpestrm(s,p);
	print128_bits(res);

	std::string str = "mississauga";
	int ind = max_suffix_duval(str,0,9);

	//printf(str.substr(ind));
	std::cout << str.substr(ind) << "\n";


	return 0;
}
