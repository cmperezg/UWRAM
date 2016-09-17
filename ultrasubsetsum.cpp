#include <math.h>
#include <cstdio>
#include <vector>
#include "ultraword.h"

//compile: g++ ultrasubsetsum.cpp ultraword.cpp -o ultrasubsetsum -std=c++11


// get bit #bitno from num. 0 is most significant.
unsigned int getbit(UltraWord num, int bitno){
	unsigned int w = UltraWord::WORD_SIZE;
	int shiftno = w-bitno-1;
	UltraWord mask;
	mask.setzeros();
	mask = 1;
	mask=mask<<shiftno;
	UltraWord maskedn = num&mask;
	UltraWord thebit = maskedn>>shiftno;
	return thebit.blocks[UltraWord::NUM_BLOCKS-1];
	
}

/* No boundary array right shift (across UltraWords) */
std::vector<UltraWord> nbars(std::vector<UltraWord>& orig, unsigned int x){
	int alength = orig.size();
	unsigned int b_s = UltraWord::WORD_SIZE;
	std::vector<UltraWord> shifted(alength);
	int i;
	//zeros loop?
	UltraWord aux1;
    UltraWord aux2;
     
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
bool isSubsetSum(std::vector<int>& set,int t){
	unsigned int w = UltraWord::WORD_SIZE;  //ultra wide word
	unsigned int wordsneeded = ceil(double(t+1)/w);
	unsigned int elements = set.size()+1;
	printf("W: %d\n",w);
	//Create table
	std::vector<std::vector<UltraWord>> table(elements, std::vector<UltraWord>(wordsneeded));
	int c,i;
	//Initialize first row // unnecesary after constructor?
	/*for(i=0;i<wordsneeded;i++){
		table[0][i].setzeros();
	}*/
	table[0][0] = 1;
	table[0][0] = table[0][0]<<(w-1);

	//Fill the table in bottom up manner
	int es,ss,ai;
	for(c=1;c<elements;c++){
		std::vector<UltraWord> aux = nbars(table.at(c-1),set.at(c-1));
		for(i=0;i<wordsneeded;i++){
			table.at(c).at(i) = table.at(c-1).at(i)|aux.at(i);
		}
	}
/*
	//UNCOMMENT THIS CODE TO PRINT TABLE
	printf("TABLE\n");
	for (int i = 0; i < elements; i++)
     {
       for (int j = 0; j < wordsneeded; j++)
          (table.at(i).at(j)).print();
       printf("\n");
     }
	
*/
     
	UltraWord one;
	//one.setzeros();
	one =1;
	UltraWord aux = (table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1));
	if((aux&one)==one){
		///*
		//Uncomment this code to print subset
		
		
		int wwr = wordsneeded-1;
		int bwr = t%w;
		int cr = elements-1;
		bool jobdone = false;
		int bt = wwr*w + bwr;
		printf("\nt: %d , SUBSET: ",t);
		while(!jobdone){
			//printf("IN LOOP\n");
			if(getbit(table.at(cr-1).at(wwr),bwr)==1){
				//printf("IN YES\n");
				cr--;
				continue;
			}else{
				//printf("IN NO\n");
				int pos = set.at(cr-1);
				printf(" %d ,",pos);
				cr--;
				bt = bt-pos;
				if(!(pos<=bwr)){
					wwr = ceil(double(bt+1)/w)-1;
				}
				bwr = bt%w;
			}
			if(wwr<=0 & bwr==0){
				jobdone=true;
			}else if(wwr<0 | bwr<0 | cr<0){
				jobdone = true;
				printf("/n Error printing subset");
			}
		}
		
		
		//*/
		return true;
	}return false;
	

}



int main(){
	
//B1
std::vector<int> set = {7,
		2,
		46,
		22,
		65,
		12,
		9,
		4,
		10,
		23,
		24,
		27,
		6,
		15,
		29,
		20,
		10,
		62,
		5,
		19
		};

     int sum = 30;

	if (isSubsetSum(set,sum) == true)
     printf("\nFound a subset with given sum\n");
  else
     printf("\nNo subset with given sum\n");
  return 0;
}
