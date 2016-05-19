/* Tests for bitwise operations on integers */

#include<stdio.h>

main()
{
    unsigned int i = 67;
    
    printf("original number is: %d \n",i);
	
	//i = i << 25;
	
	printf("after a 25 pos left shift!: %u \n",i); 
	
	//bit masking to extract most significant bit
	
	int intsize = sizeof(int);
	printf("size of int: %d \n",intsize); //4, so 32 bits.
	
	int mask = 1 << 6; //want the most significant bit
	int maskedi = i & mask;
	int thebit = maskedi >> 6;
	
	printf("most significant bit: %u \n",thebit); //should be 1 !
}
