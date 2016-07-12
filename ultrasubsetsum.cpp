#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ultraword.h"

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
	table[0][0] = 1<<(UltraWord::BLOCK_SIZE-1);
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
				aun = table[c-1][i].nbrs(ai);
				n = n|aun;
			}else if(i-es >= 0){
				aun = table[c-1][i-es].nbrs(ss);
				n = n|aun;
			}if(i-es-1 >= 0){
				aun = table[c-1][i-es-1].nbls(w-ss);
				n = n|aun;
			}
			table[c][i] = n;
		}
	}

	printf("TABLE\n");
	for (int i = 0; i < elements; i++)
     {
       for (int j = 0; j < wordsneeded; j++)
          table[i][j].print();
       printf("\n");
     }


     //not working
     
    //printf("RESULT CALC\n");
	UltraWord one;
	one.setzeros();
	one =1;
	
	UltraWord preres;
	preres = table[elements-1][wordsneeded-1].blocks[wordsneeded-1];
	int shiftnum = (w*wordsneeded)-t-1;
	//printf("shiftno =%d\n",shiftnum);
	int x = floor((t%w)/UltraWord::BLOCK_SIZE); //x = the block number to get.
	//printf("int x =%d\n",x);
	preres = preres.blocks[x];
	//printf("PRERES \n");
	//preres.print();
	preres = preres>>shiftnum;
	//printf("PRERES AFTER SHIFT\n");
	//preres.print();
	preres = preres&one;
	//printf("PRERES AFTER AND\n");
	//preres.print();
	//printf("ONE\n");
	//one.print();
	//printf("PRERES ==1  %d\n",preres==one);
    if(preres == one){
		 return true;
	 }return false;
}



int main(){
	int set[] = {81,80,43,40,30,26,12,11,9};
	int sum = 63;

	//int set[] = {1,2,3,4};
	//int sum = 10;


	int n = sizeof(set)/sizeof(set[0]);
	if (isSubsetSum(set,n,sum) == true)
     printf("Found a subset with given sum\n");
  else
     printf("No subset with given sum\n");
  return 0;
}
