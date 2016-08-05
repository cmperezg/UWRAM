    #include <math.h>
    #include <cstdio>
    #include <vector>
     //compile = g++ -o redss -g redss.cpp -std=c++11
    // get bit #bitno from num. 0 is most significant.
    
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
        printf("elem: %d, wn: %d\n",elements,wordsneeded);
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
				//printf("c,i = %d,%d\n",c,i);
                table.at(c).at(i) = table.at(c-1).at(i)|(unsigned)aux.at(i);
            }
            }
            
            
            
            
        //UNCOMMENT TO PRINT THE TABLE
        printf("TABLE\n");    
        for (int i = 0; i < elements; i++)
		{
			for (int j = 0; j < wordsneeded; j++)
			printbits(table.at(i).at(j));
			printf("\n");
		}
     //*/   
        
     
        if((table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1){
			
			
			int s = t;
			int currow = elements-1;
			int bwr = t%w;
			int wwr = wordsneeded -1;
			bool topisone;
			bool jobdone = false;
			printf("Subset: \n");
			printf("wwr: %d , bwr: %d\n",wwr,bwr);
			while((!jobdone)&currow>0){
				printf("enter loop. currow = %d\n",currow);
				topisone = getbit(table.at(currow-1).at(wwr),bwr)==1;
				if(topisone){
					printf("topisone\n");
					printf("I1 wwr: %d , bwr: %d\n",wwr,bwr);
					currow--;
				}else{
					printf("topisn't\n");
					if(wwr==0|set.at(currow-1)<=bwr){
						bwr = bwr - set.at(currow-1);
						printf("PARTOFSET : %d ,",set.at(currow-1));
						if(bwr<=0){
							jobdone = true;
						}
						printf("E1 wwr: %d , bwr: %d\n",wwr,bwr);
					}else if(set.at(currow-1)>bwr){
						bwr = (set.at(currow-1)-bwr)%w;
						wwr = wwr - ceil(set.at(currow-1)/w);
						printf("PARTOFSET :  %d ,",set.at(currow-1));
						if(bwr<=0){
							jobdone = true;
						}
						printf("E2 wwr: %d , bwr: %d\n",wwr,bwr);
					}
					currow--;
				}
				}
			
     
             return true;
         }return false;
    }
     
     
    int main(){
		
		unsigned int x = 8;
		printf("28th bit of 8 should be one = %d\n",getbit(x,28));
     
        std::vector<int> set = {81,80,43,40,30,26,12,11,9};
        int sum = 159;
        //int sum = 1000;
        
        /*
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
     */
        int n = set.size();
        if (isSubsetSum(set,sum) == true)
         printf("\nFound a subset with given sum\n");
      else
         printf("\nNo subset with given sum\n");
      return 0;
    }
