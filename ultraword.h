
class UltraWord{
	
	unsigned int blocks[NUM_BLOCKS];
	
	public: 
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
		
		UltraWord operator&(const UltraWord& u);	
		UltraWord operator|(const UltraWord& u);
		
		/*Shifts every block separately*/
		UltraWord operator<<(unsigned int shift);
		UltraWord operator>>(unsigned int shift);
		
		UltraWord operator+(const UltraWord& u);
		UltraWord operator-(const UltraWord& u);
		
};

