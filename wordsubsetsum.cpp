#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
/* Returns true if there is a subset of set[] with sum equal to t */
bool isSubsetSum(int set[],int n, int t){
	unsigned int w = sizeof(int)*8;  //for regular word.
	unsigned int wordsneeded = ceil(double(t+1)/w);
	unsigned int elements = n+1;

	//Create table
	unsigned int table[elements][wordsneeded];
	int c,i;
	//Initialize first row
	for(i=0;i<wordsneeded;i++){
		table[0][i] = 0;
	}
	table[0][0] = 1<<(w-1);
	//Fill the table in bottom up manner
	int es,ss,ai;
	for(c=1;c<elements; c++){
		ai = set[c-1];
		es = floor(ai/w);
		ss = ai%w;
		unsigned int n = 0; //word
		unsigned int aun = 0; //auxiliary word
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

	printf("TABLE\n");
	for (int i = 0; i < elements; i++)
     {
       for (int j = 0; j < wordsneeded; j++)
          printbits(table[i][j]);
       printf("\n");
     }

     //if((table[elements-1][wordsneeded-1]>>(w-t-1))&1 ==1){
	if((table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1){
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
