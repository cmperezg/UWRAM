
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

		/* boundary shifts*/
		UltraWord brs(int x);
		UltraWord bls(int x);


		/* CONSTRUCTOR */

		UltraWord();

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

		/* copy */
		void operator=(const UltraWord& u)
		{
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

