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
	printf("elements = %u , wordsneeded = %u, w = %u\n",elements,wordsneeded,w);
	//Initialize first row
	for(i=0;i<wordsneeded;i++){
		table[0][i] = 0;
	}
	table[0][0] = 1<<(w-1);
	printf("first word init: \n");
	printbits(table[0][0]);
	printf("should be fine here...\n");
	//Fill the table in bottom up manner
	int es,ss,ai;
	for(c=1;c<elements; c++){
		ai = set[c-1];
		printf("ai = %u\n",ai);
		es = floor(ai/w);
		printf("es = %u\n",es);
		ss = ai%w;
		printf("ss = %u\n",ss);
		unsigned int n = 0; //word
		unsigned int aun = 0; //auxiliary word
		for(i=0;i<wordsneeded;i++){
			n = table[c-1][i];
			printbits(n);
			if(ai<w){
				aun = table[c-1][i]>>ai;
				n = n|aun;
				printbits(n);
			}else if(i-es > 0){
				aun = table[c-1][i-es]>>ss;
				n = n|aun;
				printbits(n);
			}if(i-es-1 > 0){
				aun = table[c-1][i-es-1]<<(w-ss);
				n = n|aun;
				printbits(n);
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
     
     if((table[elements-1][wordsneeded-1]>>(w-t-1))&1 ==1){
		 return true;
	 }return false;
}



int main(){
	int set[] = {3, 34, 4, 12, 5, 2};
	int sum = 9;
	int n = sizeof(set)/sizeof(set[0]);
	if (isSubsetSum(set,n,sum) == true)
     printf("Found a subset with given sum\n");
  else
     printf("No subset with given sum\n");
  return 0;
}
