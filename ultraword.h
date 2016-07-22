
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

		/* No boundary shifts*/
		UltraWord brs(int x);
		UltraWord bls(int x);

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
		UltraWord operator<<(unsigned int x){
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
		
		

		/* No boundary right shift */
		UltraWord operator>>(unsigned int x){
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

		void operator=(unsigned int assg)
		{
			this->blocks[0] = assg;
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

