
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
				if(this->blocks[0] != u.blocks[i]){
					return false;
				}
			}
			return true;
		}

};

