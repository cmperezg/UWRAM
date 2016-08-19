    #include <math.h>
    #include <cstdio>
    #include <vector>
     //compile = g++ -o wordsubsetsum -g wordsubsetsum.cpp -std=c++11
    
    /* function to print the bits of an int */
	void printbits(unsigned int n){
	int i;
	for(i=sizeof(int)*8-1;i>=0;i--){
		unsigned int mask = 1<<i;
		unsigned int maskedn = n&mask;
		unsigned int thebit = maskedn >> i;
		printf("%u",thebit);
	}
	printf("\n");
}
    /* get bit #bitno from num. 0 is most significant */
    unsigned int getbit(unsigned int num, int bitno){
     
        unsigned int w = sizeof(int)*8;  //for regular word.
        int shiftno = w-bitno-1;
        unsigned int mask = 1<<shiftno;
        unsigned int maskedn = num&mask;
        unsigned int thebit = maskedn>>shiftno;
        return thebit;
    }
     
    /* No boundary array right shift */
    std::vector<int> nbars(std::vector<unsigned int>& orig, unsigned int x){
     
        int alength = orig.size();
        unsigned int b_s = sizeof(int)*8;
        std::vector<int> shifted(alength);
        int i;
        for(i=0;i<alength;i++){
            shifted[i] = 0;
        }
     
        unsigned int aux1 = 0;
        unsigned int aux2 = 0;
     
        int bts = floor(x/b_s);
        int split = x%b_s;
        i = bts;
        int j = 0;
        while(i<alength){
            aux1 = orig.at(j)>>split;
            shifted.at(i) = aux1|aux2;
            aux2 = orig[j]<<(b_s-split);
            i++;j++;
        }
        return shifted;
    }
     
    /* Returns true if there is a subset of set[] with sum equal to t */
    bool isSubsetSum(std::vector<int>& set, int t){
        unsigned int w = sizeof(int)*8;  //for regular word.
        unsigned int wordsneeded = ceil(double(t+1)/w);
        unsigned int elements = set.size()+1;
        //Create table
        std::vector<std::vector<unsigned int>> table(elements, std::vector<unsigned>(wordsneeded));
        int c,i;
        //Initialize first row
        for(i=0;i<wordsneeded;i++){
            table.at(0).at(i) = 0;
        }
        table[0][0] = 1<<(w-1);
        //Fill the table in bottom up manner
        int es,ss,ai;
        for(c=1;c<elements; c++){
     
            std::vector<int> aux = nbars(table.at(c-1),set.at(c-1));
            for(i=0;i<wordsneeded;i++){
                table.at(c).at(i) = table.at(c-1).at(i)|(unsigned)aux.at(i);
            }
        }
            
            
            
           /*
        //UNCOMMENT TO PRINT THE TABLE
        printf("TABLE\n");    
        for (int i = 0; i < elements; i++)
		{
			for (int j = 0; j < wordsneeded; j++)
			printbits(table.at(i).at(j));
			printf("\n");
		}
        */

     
        if((table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1){
			
		///*	
		//UNCOMMENT TO PRINT SUBSET	
			int wwr = wordsneeded-1;
			int bwr = t%w;
			int cr = elements-1;
			bool jobdone = false;
			int bt = wwr*w + bwr;
			printf("\nt: %d , SUBSET: ",t);
			while(!jobdone){
				if(getbit(table.at(cr-1).at(wwr),bwr)==1){
					cr--;
					continue;
				}else{
					int pos = set.at(cr-1);
					printf(" %d ,",pos);
					
					cr--;
					bt = bt - pos;
					if(!(pos<=bwr)){
						wwr = ceil(double(bt+1)/w) -1;
					}

					bwr = (bt%w);

				}
				if(wwr<=0 & bwr==0){
					jobdone = true;
				}else if(wwr<0 | bwr <0 | cr<0){
					jobdone = true;
					printf("/n Error printing subset");
				}
			}
			
			//*/
     
             return true;
         }return false;
    }
     
     
    int main(){


        std::vector<int> set = {1052,
		168,
		823,
		1020,
		1120,
		2350,
		67,
		880,
		2262,
		2500,
		888,
		850
		};

     int sum = 8820;

        int n = set.size();
        if (isSubsetSum(set,sum) == true)
         printf("\nFound a subset with given sum\n");
      else
         printf("\nNo subset with given sum\n");
      return 0;
    }
