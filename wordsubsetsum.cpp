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

// get bit #bitno from num. 0 is most significant.
unsigned int getbit(unsigned int num, int bitno){
	
	unsigned int w = sizeof(int)*8;  //for regular word.
	int shiftno = w-bitno;
	
	unsigned int mask = 1<<shiftno;
	unsigned int maskedn = num&mask;
	unsigned int thebit = maskedn>>shiftno;
	
	return thebit;
}

//only call this if there is a solution
/*
void printsubset(unsigned int table[][], int t, int elem){
	printf("Subset: \n");
	unsigned int w = sizeof(int)*8; 
	int s = t; //sum left to account for
	int bwr = (w*wordsneeded)-t-1; // bit with result (0 indexing)
	int wwr = wordsneeded -1; //0 indexing
	while(s>0){
		bool topisone = true;
		int currrow = elem;
		//get last element 
		while(topisone && currrow>0){
			topisone = (getbit(table[currrow-1][wwr],bwr) == 1);
			if(topisone){
				currrow --;
				bwr = bwr - elements[currow];
			}
		}
		printf("%d , " ,elements[currow];);
	}
	//if((table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1)
}*/
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
	if((table[elements][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1){
		//printsubset(table,t,elements);
		
		//Uncomment this code to print subset
		/*
		printf("Subset: \n");
		//unsigned int w = sizeof(int)*8; 
		int s = t; //sum left to account for
		int bwr = (w*wordsneeded)-t-1; // bit with result (0 indexing)
		int wwr = wordsneeded -1; //0 indexing
		int currrow = elements;
		while(s>0){
			bool topisone = true;
			
			//get last element 
			while(topisone && currrow>0){
				topisone = (getbit(table[currrow-1][wwr],bwr) == 1);
				if(topisone){
					currrow --;
					bwr = bwr - set[currrow];
				}
			}
			printf("%d , " ,set[currrow]);
		}*/
		int s = t;
		int currrow = elements;
		int bwr = (w*wordsneeded)-t-1; // bit with result (0 indexing)
		int wwr = wordsneeded -1; //0 indexing
		bool topisone;
		topisone = (getbit(table[currrow-1][wwr],bwr) == 1);
		printf("s = %d, currrow = %d, topisone = %d \n",s,currrow,topisone);
		currrow--;
		topisone = (getbit(table[currrow-1][wwr],bwr) == 1);
		printf("s = %d, currrow = %d, topisone = %d \n",s,currrow,topisone);
		
		 return true;
	 }return false;
}


int main(){
	//int set[] = {81,80,43,40,30,26,12,11,9};
	//int sum = 63;

	int set[] = {3,34,4,12,5};
	int sum = 9;

	int n = sizeof(set)/sizeof(set[0]);
	if (isSubsetSum(set,n,sum) == true)
     printf("Found a subset with given sum\n");
  else
     printf("No subset with given sum\n");
  return 0;
}
