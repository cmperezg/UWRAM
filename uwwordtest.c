/* wide word operation tests */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_OF_INT  4 
#define SIZE_OF_BYTE  8
#define NUM_BLOCKS  32

typedef struct{
	unsigned int blocks[NUM_BLOCKS];
} WWord;

/* function declarations */
WWord and(WWord *a, WWord *b);
WWord or(WWord *a, WWord *b);
WWord xor(WWord *a, WWord *b);
WWord compress(WWord *w);

void printbits(unsigned int n);
void printwword(WWord *word);
void fillword(WWord *word);
void setzeros(WWord *word);



int main(void){
	
	/* Intializes random number generator */
	time_t t;
    srand((unsigned) time(&t));
    //printf("%u\n",SIZE_OF_INT*SIZE_OF_BYTE-1);
    
	WWord testword1;
	WWord testword2;
	fillword(&testword1); 
	//fillword(&testword2);
	printwword(&testword1);
	//printwword(&testword2);
	
	/* Testing operations */
	//WWord result = xor(&testword1,&testword2);
	WWord result = compress(&testword1);
	printwword(&result);
	
}

/* Operation definitions  for WWord */

WWord and(WWord *a, WWord *b){
	int i;
	WWord ret;
	for(i = 0; i<NUM_BLOCKS; i++){
		ret.blocks[i] = a->blocks[i] & b->blocks[i];
	}
	return ret;
}

WWord or(WWord *a, WWord *b){
	int i;
	WWord ret;
	for(i = 0; i<NUM_BLOCKS; i++){
		ret.blocks[i] = a->blocks[i] | b->blocks[i];
	}
	return ret;
}

WWord xor(WWord *a, WWord *b){
	int i;
	WWord ret;
	for(i = 0; i<NUM_BLOCKS; i++){
		ret.blocks[i] = a->blocks[i] ^ b->blocks[i];
	}
	return ret;
}

WWord compress(WWord *w){
	unsigned int firstmask = 1<<SIZE_OF_INT*SIZE_OF_BYTE-1;
	int i;
	WWord compressed;
	setzeros(&compressed);
	//printwword(&compressed);
	for(i=0; i<NUM_BLOCKS; i++){
		unsigned int maskedn = w->blocks[i]&firstmask;
		unsigned int thebit = maskedn >> SIZE_OF_INT*SIZE_OF_BYTE-1;
		compressed.blocks[0] = compressed.blocks[0] << 1;
		compressed.blocks[0] = compressed.blocks[0] | thebit;
	}
	return compressed;
}

//function to print the bits of an int.
void printbits(unsigned int n){
	int i;
	//printf("%u = ",n);
	for(i=SIZE_OF_INT*SIZE_OF_BYTE-1;i>=0;i--){
		unsigned int mask = 1<<i;
		unsigned int maskedn = n&mask;
		unsigned int thebit = maskedn >> i;
		printf("%u",thebit);
	}
	printf("\n");
}

//prints full word, 1 block per line
void printwword(WWord *word){
	int i;
	printf("WORD: \n");
	for(i=0; i<NUM_BLOCKS;i++){
		printbits(word->blocks[i]);
		//printf("%u \n",word.blocks[i]);
	}
}
	
// fills word with random numbers
void fillword(WWord *word){
	int i;
	for(i=0; i<NUM_BLOCKS;i++){
		unsigned int ran = rand();
		ran = ran<<1;
		word->blocks[i] = ran;
		//word->blocks[i]<<1;
		//printf("\n");
	}
}

void setzeros(WWord *word){
	int i;
	for(i=0;i<NUM_BLOCKS;i++){
		word->blocks[i] = 0;
	}
}

