#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ultraword.h"

//compile: g++ ultrasubsetsum.cpp ultraword.cpp -o ultrasubsetsum


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

/* Returns true if there is a subset of set[] with sum equal to t */
bool isSubsetSum(int set[],int n, int t){
	unsigned int w = UltraWord::WORD_SIZE;  //ultra wide word
	unsigned int wordsneeded = ceil(double(t+1)/w);
	unsigned int elements = n+1;

	//Create table
	UltraWord table[elements][wordsneeded];
	int c,i;
	//Initialize first row
	for(i=0;i<wordsneeded;i++){
		table[0][i].setzeros();
	}
	table[0][0] = 1;
	table[0][0] = table[0][0]<<(w-1);
	//Fill the table in bottom up manner
	int es,ss,ai;
	for(c=1;c<elements; c++){
		ai = set[c-1];
		es = floor(ai/w);
		ss = ai%w;
		UltraWord n; //word
		n.setzeros();
		UltraWord aun; //auxiliary word
		aun.setzeros();
		for(i=0;i<wordsneeded;i++){
			n = table[c-1][i];
			if(ai<w){
				aun = table[c-1][i]>>ai;
				n = n|aun;
			}else if(i-es >= 0){
				aun = table[c-1][i-es]>>ss;
				n = n|aun;
			}if(i-es-1 >= 0){
				aun = table[c-1][i-es-1]<<(w-ss);
				n = n|aun;
			}
			table[c][i] = n;
		}
	}
/*
	//UNCOMMENT THIS CODE TO PRINT TABLE
	printf("TABLE\n");
	for (int i = 0; i < elements; i++)
     {
       for (int j = 0; j < wordsneeded; j++)
          table[i][j].print();
       printf("\n");
     }

*/
     
	UltraWord one;
	one.setzeros();
	one =1;
	UltraWord aux = (table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1));
	if((aux&one)==one){
		//Uncomment this code to print subset
		int currrow = elements;
		int bwr = t%w;
		int wwr = wordsneeded-1;
		bool topisone;
		bool jobdone = false;
		printf("Subset: \n");
		while(!jobdone){
			topisone = (getbit(table[currrow-1][wwr],bwr) == 1);
			if(topisone){
				currrow--;
			}else{
				if(wwr==0 || set[currrow-1]<=bwr){
					bwr = bwr - set[currrow-1];
					printf("%d  " ,set[currrow-1]);
					if(bwr <= 0){
						jobdone = true;
					}
				}else if(set[currrow-1]>bwr){
					bwr = (set[currrow -1]-bwr)%w;
					wwr = wwr - ceil(set[currrow-1]/w);
					printf("%d , " ,set[currrow-1]);
					if(bwr <= 0){
						jobdone = true;
					}
				}
			}
		}
		return true;
	}return false;
	

}



int main(){
	int set[] = {518533,
	 1037066,
     2074132,
     1648264,
      796528,
     1593056,
      686112,
     1372224,
      244448,
      488896,
      977792,
     1955584,
     1411168,
      322336,
      644672,
     1289344,
       78688,
      157376,
      314752,
      629504,
     1259008};
     int sum = 2463098;
	
	//int set[] = {81,80,43,40,30,26,12,11,9};
	//int sum = 63;

	//int set[] = {1,2,3,4};
	//int sum = 10;


	int n = sizeof(set)/sizeof(set[0]);
	if (isSubsetSum(set,n,sum) == true)
     printf("Found a subset with given sum\n");
  else
     printf("No subset with given sum\n");
  return 0;
}
