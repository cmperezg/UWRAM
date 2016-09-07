#include <cstdio>

int SIZE_OF_INT = 8;  //long long int for this test
int SIZE_OF_BYTE = 8;
int NUM_BLOCKS = 32;
int BLOCK_SIZE = SIZE_OF_INT * SIZE_OF_BYTE;
int WORD_SIZE = BLOCK_SIZE * NUM_BLOCKS;


/* function to print the bits of an int */
void printbits(unsigned long long int n){
	long long int i;
	for(i=SIZE_OF_INT*SIZE_OF_BYTE-1;i>=0;i--){
		unsigned long long int mask = ((unsigned long long int)1)<<i;
		unsigned long long int maskedn = n&mask;
		unsigned long long int thebit = maskedn >> i;
		printf("%u",(unsigned int)thebit);
		//printf("%llu",n);
	}
	//printf("%llu",n);
	printf("\n");
}
int main(){
	int l = sizeof(long long int);
	printf("size of long long int: %d \n",l);
	
	unsigned long long int t = ((unsigned long long int)1)<<32;
	printf("size of long long int: %llu \n",t);
	printbits(t);
	
	return 0;
}
