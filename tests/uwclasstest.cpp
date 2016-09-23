#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ultraword.h"

int main(){
	UltraWord u;
	u.setzeros();

	u.print();

	int wordsize = UltraWord::WORD_SIZE;

	u = 1;
	//u.blocks[0] = 1;
	u.nbls(UltraWord::BLOCK_SIZE-1);

	u.print();
  return 0;
}