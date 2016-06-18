#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE_OF_INT  4 
#define SIZE_OF_BYTE  8
#define NUM_BLOCKS  32
#define BLOCK_SIZE  SIZE_OF_INT * SIZE_OF_BYTE

class UltraWord{
	
	unsigned int blocks[NUM_BLOCKS];
	
	public: 
		void print();
		void randomfill();
		void setzeros();
		void printbits(unsigned int n);
		
		UltraWord compress();
		UltraWord spread();
		UltraWord nbrs(int x);
		UltraWord nbls(int x);
	
		/* OPERATOR OVERLOADING */
		
		UltraWord operator&(const UltraWord& u)
		{
			UltraWord word;
			
			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i] & u.blocks[i];
			}
			return word;
		}
		
		UltraWord operator|(const UltraWord& u)
		{
			UltraWord word;
			
			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i] | u.blocks[i];
			}
			return word;
		}
		/*Shifts every block separately*/
		UltraWord operator<<(unsigned int shift)
		{
			UltraWord word;
			
			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i]<<shift;
			}
			return word;
		}
		
		/*Shifts every block separately*/
		UltraWord operator>>(unsigned int shift)
		{
			UltraWord word;
			
			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i]>>shift;
			}
			return word;
		}
		
		UltraWord operator+(const UltraWord& u)
		{
			UltraWord word;
			
			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i] + u.blocks[i];
			}
			return word;
		}
		
		UltraWord operator-(const UltraWord& u)
		{
			UltraWord word;
			
			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i] - u.blocks[i];
			}
			return word;
		}
		
};

/* OTHER ULTRAWORD FUNCTIONS */
UltraWord UltraWord::compress(){
	unsigned int firstmask = 1<<SIZE_OF_INT*SIZE_OF_BYTE-1;
	int i;
	UltraWord compressed;
	compressed.setzeros();
	for(i=0; i<NUM_BLOCKS; i++){
		unsigned int maskedn = this->blocks[i]&firstmask;
		unsigned int thebit = maskedn >> SIZE_OF_INT*SIZE_OF_BYTE-1;
		compressed.blocks[0] = compressed.blocks[0] << 1;
		compressed.blocks[0] = compressed.blocks[0] | thebit;
	}
	return compressed;
}

UltraWord UltraWord::spread(){
	int i;
	UltraWord expanded;
	unsigned int shiftcount = 0;
	for(i=NUM_BLOCKS-1; i>=0; i--){
		unsigned int mask = 1<<shiftcount;
		unsigned int maskedn = this->blocks[0]&mask;
		unsigned int thebit = maskedn >> shiftcount;
		expanded.blocks[i] = thebit<<SIZE_OF_INT*SIZE_OF_BYTE-1;
		shiftcount++;
	}
	return expanded;
}

/* No boundary right shift >> */
UltraWord UltraWord::nbrs(int x){
	UltraWord shifted;
	unsigned int au = 0;
	unsigned int au2 = 0;
	unsigned int m = 0;
	unsigned int aushift = BLOCK_SIZE - x;
	int c;
	/* create mask */
	for(c = 0; c<x; c++){
		m = (m<<1)|1;
	}
	/* first block special case */
	au = blocks[0]&m;
	au = au<<aushift;
	shifted.blocks[0] = this->blocks[0]>>x;
	/* middle blocks */
	for(c=1; c<NUM_BLOCKS-1; c++){
		au2 = this->blocks[c]&m;
		au2 = au2<<aushift;
		shifted.blocks[c] = this->blocks[c]>>x;
		shifted.blocks[c] = shifted.blocks[c]|au;
		au = au2;
	}
	/* last block special case */
	shifted.blocks[NUM_BLOCKS-1] = (this->blocks[NUM_BLOCKS-1]>>x)| au;
	return shifted;
}

/* No boundary left shift << */
UltraWord UltraWord::nbls(int x){
	UltraWord shifted;
	unsigned int au = 0;
	unsigned int au2 = 0;
	unsigned int m = 0;
	unsigned int aushift = BLOCK_SIZE - x;
	int c;
	/* create mask */
	for(c = 0; c<x; c++){
		m = (m<<1)|1;
	}
	m = m<<aushift;
	/* first block special case */
	au = blocks[NUM_BLOCKS-1]&m;
	au = au<<aushift;
	shifted.blocks[NUM_BLOCKS-1] = this->blocks[NUM_BLOCKS-1]>>x;
	/* middle blocks */
	for(c=NUM_BLOCKS-1; c>0; c--){
		au2 = this->blocks[c]&m;
		au2 = au2>>aushift;
		shifted.blocks[c] = this->blocks[c]<<x;
		shifted.blocks[c] = shifted.blocks[c]|au;
		au = au2;
	}
	/* last block special case */
	shifted.blocks[0] = (this->blocks[0]<<x)| au;
	return shifted;
}
	
/* ULTRAWORD UTILITIES */
/* function to print the bits of an int */
void UltraWord::printbits(unsigned int n){
	int i;
	for(i=SIZE_OF_INT*SIZE_OF_BYTE-1;i>=0;i--){
		unsigned int mask = 1<<i;
		unsigned int maskedn = n&mask;
		unsigned int thebit = maskedn >> i;
		printf("%u",thebit);
	}
	printf("\n");
}

/* prints full word, 1 block per line */
void UltraWord::print(){
	int i;
	printf("WORD: \n");
	for(i=0; i<NUM_BLOCKS;i++){
		printbits(this->blocks[i]);
	}
}
		
/* fills word with random numbers */
void UltraWord::randomfill(){
	int i;
	for(i=0; i<NUM_BLOCKS;i++){
		unsigned int ran = rand();
		ran = ran<<1;
		this->blocks[i] = ran;
	}
}
	
/* fills word with zeros */
void UltraWord::setzeros(){
	int i;
	for(i=0;i<NUM_BLOCKS;i++){
		this->blocks[i] = 0;
	}
}
	
int main(void){
	time_t t;
    srand((unsigned) time(&t));
    
    UltraWord w1;
    //UltraWord w2;
    
    w1.randomfill();
    //w2.randomfill();
    
    w1.print();
    //w2.print();
    
    UltraWord res = w1.nbls(3);
    res.print();

   
}	
	
	
