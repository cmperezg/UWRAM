/* Tests for bitwise operations on integers */

#include<stdio.h>

main()
{
    unsigned int i = 67;
    
    printf("original number is: %d \n",i);
	/*
	//i = i << 25;
	
	printf("after a 25 pos left shift!: %u \n",i); 
	
	//bit masking to extract most significant bit
	
	int intsize = sizeof(int);
	printf("size of int: %d \n",intsize); //4, so 32 bits.
	
	int mask = 1 << 6; //want the most significant bit
	int maskedi = i & mask;
	int thebit = maskedi >> 6;
	
	printf("most significant bit: %u \n",thebit); //should be 1 !
	 */
	 printbits(i);
}

//function to print the bits of an int.
printbits(int n){
	int i;
	printf("%u = ",n);
	for(i=31;i>=0;i--){
		int mask = 1<<i;
		int maskedn = n&mask;
		int thebit = maskedn >> i;
		printf("%u",thebit);
	}
	printf("\n");
}
