#include <math.h>
#include <cstdio>
#include <vector>
#include <chrono>
#include <tuple>
#include "ultraword.h"

//compile: g++ timednof.cpp ultraword.cpp -o timednof -std=c++11
    
bool isSubsetSum(std::vector<int>& set, int t){	
	 
	int c,i;
	
    unsigned int w = sizeof(int)*8;  //for regular word.
    unsigned int wordsneeded = ceil(double(t+1)/w);
    unsigned int elements = set.size()+1;
    //Create table
    std::vector<std::vector<unsigned int>> table(elements, std::vector<unsigned>(wordsneeded));
    //Initialize first row
    table[0][0] = 1<<(w-1);

    //Fill the table in bottom up manner
    int es,ss,ai,j,k,x;
    int alength = table.at(0).size();
    for(c=1;c<elements; c++){
		x = set.at(c-1);
		std::vector<unsigned int> orig = table.at(c-1);
		std::vector<int> aux(alength);
		unsigned int aux1 = 0;
        unsigned int aux2 = 0;
		
        int bts = floor(x/w);
        int split = x%w;
        j = bts;
        k = 0;
        
        while(j<alength){
            aux1 = orig.at(k)>>split;
            aux.at(j) = aux1|aux2;
            aux2 = orig[k]<<(w-split);
            j++;k++;
		}
            
            for(i=0;i<wordsneeded;i++){
                table.at(c).at(i) = table.at(c-1).at(i)|(unsigned)aux.at(i);
            }
        }
		bool ec = (table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1;
        if(ec){
             return true;
         }return false;
    }
    
    
    
//ULTRA SUBSET SUM


/* Returns true if there is a subset of set[] with sum equal to t */
bool isSubsetSumUW(std::vector<int>& set,int t){
	int c,i;
	
	unsigned int w = UltraWord::WORD_SIZE;  //ultra wide word
	unsigned int wordsneeded = ceil(double(t+1)/w);
	unsigned int elements = set.size()+1;
	//Create table
	std::vector<std::vector<UltraWord>> table(elements, std::vector<UltraWord>(wordsneeded));
	
	//Initialize first row 
	table[0][0] = 1;
	table[0][0] = table[0][0]<<(w-1);
	//Fill the table in bottom up manner
	int es,ss,ai,j,k,x;
	int alength = table.at(0).size();
	for(c=1;c<elements;c++){
		x = set.at(c-1);
		std::vector<UltraWord> orig = table.at(c-1);
		std::vector<UltraWord> aux(alength);
		
		UltraWord aux1;
		UltraWord aux2;
		int bts = floor(x/w);
		int split = x%w;
		j = bts;
		k = 0;
		while(j<alength){
			aux1 = orig.at(k)>>split;
			aux.at(j) = aux1|aux2;
			aux2 = orig[k]<<(w-split);
			j++;k++;
		}
		for(i=0;i<wordsneeded;i++){
			table.at(c).at(i) = table.at(c-1).at(i)|aux.at(i);
		}
	}

     
	UltraWord one;
	one =1;
	UltraWord aux = (table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1));
	bool ec = (aux&one)==one;
	if(ec){
		return true;
	}return false;
	

}    
    
int main(){
	
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
     bool result = isSubsetSum(set,sum);
     
     if(result){
		 printf("\nFound a subset with given sum\n");
	 }else{
		 printf("\nNo subset with given sum\n");
	 }
	 
	 bool UWresult = isSubsetSumUW(set,sum);
     
     if(UWresult){
		 printf("\nUW Found a subset with given sum\n");
	 }else{
		 printf("\nUW No subset with given sum\n");
	 }
}
