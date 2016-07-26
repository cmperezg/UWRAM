#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*#define SIZE_OF_INT  4
#define SIZE_OF_BYTE  8
#define NUM_BLOCKS  32
#define BLOCK_SIZE  SIZE_OF_INT * SIZE_OF_BYTE
#define WORD_SIZE  NUM_BLOCKS * BLOCK_SIZE*/

class UltraWord{

	public:

		static int SIZE_OF_INT;
		static int SIZE_OF_BYTE;
		static int NUM_BLOCKS;
		static int BLOCK_SIZE;
		static int WORD_SIZE;

		unsigned int blocks[32];

		void print();
		void randomfill();
		void setzeros();
		void printbits(unsigned int n);

		UltraWord compress();
		UltraWord spread();
		UltraWord brs(int x);
		UltraWord bls(int x);

		/* OPERATOR OVERLOADING */

		UltraWord operator&(const UltraWord& u){
			UltraWord word;

			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i] & u.blocks[i];
			}
			return word;
		}

		UltraWord operator|(const UltraWord& u){
			UltraWord word;

			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i] | u.blocks[i];
			}
			return word;
		}
		
		/*No boundary left shift*/
		UltraWord operator<<(unsigned int x){
			UltraWord shifted;
			shifted.setzeros();
			unsigned int aux1 = 0;
			unsigned int aux2 = 0;
			
			int bts = floor(x/BLOCK_SIZE);
			int split = x%BLOCK_SIZE;
			int i = bts;
			int j = 0;
			while(i<NUM_BLOCKS){
				//printf("i=%d, j=%d \n",i,j);
				aux1 = this->blocks[i]<<split;
				if((i+1)<NUM_BLOCKS){
					aux2=this->blocks[i+1]>>(BLOCK_SIZE-split);
				}else{
					aux2 = 0;
				}
				shifted.blocks[j] = aux1|aux2;
				j++;i++;
			}
			return shifted;
		}

		/* No boundary right shift */
		UltraWord operator>>(unsigned int x){
			UltraWord shifted;
			shifted.setzeros();
			unsigned int aux1 = 0;
			unsigned int aux2 = 0;
			
			int bts = floor(x/BLOCK_SIZE);
			int split = x%BLOCK_SIZE;
			int i = bts;
			int j = 0;
			//printf("bts=%d \n",bts);
			//printf("split=%d \n",split);
			while(i<NUM_BLOCKS){
				//printf("i=%d, j=%d \n",i,j);
				aux1 = this->blocks[j]>>split;
				shifted.blocks[i] = aux1|aux2;
				aux2 = this->blocks[j]<<(BLOCK_SIZE-split);
				i++;j++;
			}
			return shifted;
		}

		UltraWord operator+(const UltraWord& u){
			UltraWord word;

			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i] + u.blocks[i];
			}
			return word;
		}

		UltraWord operator-(const UltraWord& u){
			UltraWord word;

			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				word.blocks[i] = this->blocks[i] - u.blocks[i];
			}
			return word;
		}

		/* copy */
		void operator=(const UltraWord& u){
			int i;
			for(i = 0; i<NUM_BLOCKS; i++){
				this->blocks[i] = u.blocks[i];
			}
		}

		/* Assign int to last block of a word */
		void operator=(unsigned int assg){

			this->blocks[NUM_BLOCKS-1] = assg;
		}

		/* Equals. checks all blocks are the same bitwise */
		bool operator==(const UltraWord& u){
			int i;
			bool res = true;
			for(i = 0; i<NUM_BLOCKS; i++){
				if(this->blocks[i] != u.blocks[i]){
					return false;
				}
			}
			return true;
		}

};

int UltraWord::SIZE_OF_INT = 4;
int UltraWord::SIZE_OF_BYTE = 8;
int UltraWord::NUM_BLOCKS = 32;
int UltraWord::BLOCK_SIZE = SIZE_OF_INT * SIZE_OF_BYTE;
int UltraWord::WORD_SIZE = BLOCK_SIZE * NUM_BLOCKS;

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

/* Boundary right shift >> */
UltraWord UltraWord::brs(int x){
	UltraWord word;

	int i;
	for(i = 0; i<NUM_BLOCKS; i++){
		word.blocks[i] = this->blocks[i]>>x;
	}
	return word;
}

/* Boundary left shift << */
UltraWord UltraWord::bls(int x){
	UltraWord word;

	int i;
	for(i = 0; i<NUM_BLOCKS; i++){
		word.blocks[i] = this->blocks[i]<<x;
	}
	return word;
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
/*
int main(void){
	time_t t;
    srand((unsigned) time(&t));

    UltraWord w1,w2;
	w1.setzeros();
	w2.setzeros();
    //w1 = 3;

    
	//(w1<<100).print();
	//w1.blocks[0] =1<<31;
	//w1.randomfill();
	w1 = 3;
	w1.print();
	w1 = w1<<100;
	w1.print();

    //UltraWord sum = w1+w2;

    //sum.print();


}*/


