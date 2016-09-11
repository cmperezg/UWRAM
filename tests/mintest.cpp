#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
//compile: g++ mintest.cpp -o mintest -std=c++11


class UltraWord{

	public:

		static int SIZE_OF_INT;
		static int SIZE_OF_BYTE;
		static int NUM_BLOCKS;
		static int BLOCK_SIZE;
		static int WORD_SIZE;

		unsigned long long int blocks[64];

		void print();
		void randomfill();
		void setzeros();
		void printbits(unsigned long long int n);

		UltraWord compress();
		UltraWord spread();
		UltraWord brs(int x);
		UltraWord bls(int x);
		
		/* CONSTRUCTOR */
		
		UltraWord();

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
		UltraWord operator<<(unsigned long long int x){
			UltraWord shifted;
			//shifted.setzeros();
			unsigned long long int aux1 = 0;
			unsigned long long int aux2 = 0;
			
			long long int bts = floor(x/BLOCK_SIZE);
			long long int split = x%BLOCK_SIZE;
			int i = bts;
			int j = 0;
			while(i<NUM_BLOCKS){
				//printf("i=%d, j=%d \n",i,j);
				aux1 = 0;
				aux1 = this->blocks[i]<<split;
				if(((i+1)<NUM_BLOCKS)&&x!=BLOCK_SIZE){
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
		UltraWord operator>>(unsigned long long int x){
			UltraWord shifted;
			shifted.setzeros();
			unsigned long long int aux1 = 0;
			unsigned long long int aux2 = 0;
			
			long long int bts = floor(x/BLOCK_SIZE);
			long long int split = x%BLOCK_SIZE;
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
		void operator=(unsigned long long int assg){
			//printf("in equals. NUM_BLOCKS = %d\n",NUM_BLOCKS);
			//printf("assg = %llu\n",assg);
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

int UltraWord::SIZE_OF_INT = 8;  //long long int for this test
int UltraWord::SIZE_OF_BYTE = 8;
int UltraWord::NUM_BLOCKS = 64;
int UltraWord::BLOCK_SIZE = SIZE_OF_INT * SIZE_OF_BYTE;
int UltraWord::WORD_SIZE = BLOCK_SIZE * NUM_BLOCKS;

UltraWord::UltraWord(){
	this->setzeros();
}

/* OTHER ULTRAWORD FUNCTIONS */
UltraWord UltraWord::compress(){
	unsigned int firstmask = 1<<SIZE_OF_INT*SIZE_OF_BYTE-1;
	int i;
	UltraWord compressed;
	compressed.setzeros();
	for(i=0; i<NUM_BLOCKS; i++){
		unsigned long long int maskedn = this->blocks[i]&firstmask;
		unsigned long long int thebit = maskedn >> SIZE_OF_INT*SIZE_OF_BYTE-1;
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
		unsigned long long int mask = ((unsigned long long int)1)<<shiftcount;
		unsigned long long int maskedn = this->blocks[0]&mask;
		unsigned long long int thebit = maskedn >> shiftcount;
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
void UltraWord::printbits(unsigned long long int n){
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
		unsigned long long int ran = rand();
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
	std::vector<std::vector<UltraWord>> table(10, std::vector<UltraWord>(4));
}



