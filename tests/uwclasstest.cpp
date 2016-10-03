#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ultraword.h"

//compile: g++ uwclasstest.cpp ultraword.cpp -o uwclasstest -std=c++11

int main(){
	UltraWord u;
	u.setzeros();

	u.print();

	int wordsize = UltraWord::WORD_SIZE;
	int blocksize = UltraWord::BLOCK_SIZE;
	int numblocks = UltraWord::NUM_BLOCKS;
	
	printf("wordsize: %d\n",wordsize);
	printf("blocksize: %d\n",blocksize);
	printf("numblocks: %d\n",numblocks);
	
	printf("sizeof char: %lu\n",sizeof(char));
	char z = 'z';
	printf("z: %f\n",log('z'));
	printf("logchar: %f\n",log('z'));
	printf("logchar: %f\n",log(z));
	//u = 1;
	//u.blocks[0] = 1;
	//u.nbls(UltraWord::BLOCK_SIZE-1);

	//u.print();
  return 0;
}
