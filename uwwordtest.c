//wide word operation tests

#include <stdio.h>
#include <stdlib.h>

int SIZE_OF_INT = 4; //also block size
int SIZE_OF_BYTE = 8;
int NUM_BLOCKS = 32;

struct wword{
	int blocks[NUM_BLOCKS];
}

main(){

	struct wword testword; 
	
}

//function to print the bits of an int.
printbits(int n){
	int i;
	printf("%u = ",n);
	for(i=SIZE_OF_INT*SIZE_OF_BYTE-1;i>=0;i--){
		int mask = 1<<i;
		int maskedn = n&mask;
		int thebit = maskedn >> i;
		printf("%u",thebit);
	}
	printf("\n");
}

printwword(wword word){
	int i;
	printf("%u = ",n);
	for(i=0; i<NUM_BLOCKS;i++){
		printbits(word.blocks[i]);
	}
}
