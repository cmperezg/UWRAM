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
	int shiftno = w-bitno-1;
	unsigned int mask = 1<<shiftno;
	unsigned int maskedn = num&mask;
	unsigned int thebit = maskedn>>shiftno;
	return thebit;
}

/* No boundary array left shift */
/*
unsigned int* nbals(unsigned int orig[], unsigned int x){
	
	int alength = sizeof(orig)/sizeof(orig[0]);
	unsigned int b_s = sizeof(int)*8;
	unsigned int shifted[alength];
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
		aux1 = orig[i]<<split;
		if((i+1)<alength){
			aux2 = orig[i+1]>>(b_s-split);
		}else{
			aux2 = 0;
		}
		shifted[j] = aux1|aux2;
		j++;i++;
	}
	
	return shifted;
}*/

/* No boundary array right shift */
unsigned int* nbars(unsigned int orig[], unsigned int x){
	
	int alength = sizeof(orig)/sizeof(orig[0]);
	unsigned int b_s = sizeof(int)*8;
	unsigned int * shifted;
	shifted = new unsigned int[alength];
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
		aux1 = orig[j]>>split;
		shifted[i] = aux1|aux2;
		aux2 = orig[j]<<(b_s-split);
		i++;j++;
	}
	
	return shifted;
}

/* Returns true if there is a subset of set[] with sum equal to t */
bool isSubsetSum(int set[],int n, int t){
	printf("printit\n");
	unsigned int w = sizeof(int)*8;  //for regular word.
	unsigned int wordsneeded = ceil(double(t+1)/w);
	unsigned int elements = n;
	printf("wordsneeded=%d\n",wordsneeded);
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
	for(c=1;c<=elements; c++){

		printf("c = %d",c);
		
		unsigned int *aux = nbars(table[c-1],set[c-1]);
		for(i=0;i<wordsneeded;i++){
			table[c][i] = table[c-1][i]|aux[i];
		}
		}
		
		//unsigned int n = 0; //word
	
	
	///*
	//UNCOMMENT THIS CODE TO PRINT TABLE
	printf("TABLE\n");
	for (int i = 0; i <= elements; i++)
     {
       for (int j = 0; j < wordsneeded; j++)
          printbits(table[i][j]);
       printf("\n");
     }
     //*/

     
	if((table[elements][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1){

		
		
		///*
		//Uncomment this code to print subset
		int s = t;
		int currrow = elements;
		int bwr =  t%w; // bit with result (0 indexing)
		int wwr = wordsneeded -1; //0 indexing
		bool topisone;
		bool jobdone = false;
		printf("Subset: \n");
		while(!jobdone){
			topisone = (getbit(table[currrow-1][wwr],bwr) == 1);
			if(topisone){
					currrow --;
			}else{
				if(wwr==0 || set[currrow-1]<=bwr){
					bwr = bwr - set[currrow-1];
					printf("%d , " ,set[currrow-1]);
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
				//currrow--;
				
			}
		}//*/

		 return true;
	 }return false;
}


int main(){
	/*
	int set[] = {1052,
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

	int set[] = {81,80,43,40,30,26,12,11,9};
	//int sum = 63;
	int sum = 1000;
	
	//int set[] = {50,83};
	//int sum = 1303;

	int n = sizeof(set)/sizeof(set[0]);
	printf("n = %d\n",n);
	if (isSubsetSum(set,n,sum) == true)
     printf("\nFound a subset with given sum\n");
  else
     printf("\nNo subset with given sum\n");
  return 0;
}
