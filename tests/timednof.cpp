#include <math.h>
#include <cstdio>
#include <vector>
#include <chrono>
#include <tuple>
#include <fstream>
#include "ultraword.h"

//compile: g++ timednof.cpp ultraword.cpp -o timednof -std=c++11
    
std::tuple<bool,int,int,int,int,int,int,int> isSubsetSum(std::vector<int>& set, int t){	
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	int tott = 0;
	
	int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, ct3 = 0, ct4 = 0, ct5 = 0;
	begin = std::chrono::steady_clock::now();
	int c,i;
	end = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	
	
	//T1
	begin = std::chrono::steady_clock::now();
	
    unsigned int w = sizeof(int)*8;  //for regular word.
    
    end = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	t1 = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
    
    begin = std::chrono::steady_clock::now();
    
    unsigned int wordsneeded = ceil(double(t+1)/w);
    unsigned int elements = set.size()+1;
    int es,ss,ai,j,k,x;
    
    end = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	
	
	//T2
	begin = std::chrono::steady_clock::now();
    //Create table
    std::vector<std::vector<unsigned int>> table(elements, std::vector<unsigned>(wordsneeded));
    //Initialize first row
    table[0][0] = 1<<(w-1);
	int alength = table.at(0).size();
	
	end = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	t2 = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	
    //Fill the table in bottom up manner
    begin = std::chrono::steady_clock::now();
    
    for(c=1;c<elements; c++){
		x = set.at(c-1);
		
		end = std::chrono::steady_clock::now();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		
		//T3
		begin = std::chrono::steady_clock::now();
		
		std::vector<unsigned int> orig = table.at(c-1);
		std::vector<int> aux(alength);
		unsigned int aux1 = 0;
        unsigned int aux2 = 0;
		end = std::chrono::steady_clock::now();
		t3 = t3 + std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		ct3++;
		
		begin = std::chrono::steady_clock::now();
		
        int bts = floor(x/w);
        int split = x%w;
        j = bts;
        k = 0;
        
        while(j<alength){
			end = std::chrono::steady_clock::now();
			tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
			
			//T4
			begin = std::chrono::steady_clock::now();
            aux1 = orig.at(k)>>split;
            aux.at(j) = aux1|aux2;
            aux2 = orig[k]<<(w-split);
            end = std::chrono::steady_clock::now();
			t4 = t4 + std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
			ct4++;
            
            begin = std::chrono::steady_clock::now();
            j++;k++;
		}
		end = std::chrono::steady_clock::now();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            
        
        begin = std::chrono::steady_clock::now();    
            
		for(i=0;i<wordsneeded;i++){
			end = std::chrono::steady_clock::now();
			tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
			
			//T5
			begin = std::chrono::steady_clock::now(); 
			table.at(c).at(i) = table.at(c-1).at(i)|(unsigned)aux.at(i);
			end = std::chrono::steady_clock::now();
			t5 = t5 + std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
			ct5++;
			begin = std::chrono::steady_clock::now(); 
		}
	}
        
	end = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	
	//T6
	begin = std::chrono::steady_clock::now();
	bool ec = (table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1;
	end = std::chrono::steady_clock::now();
	t6 = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	
	tott = tott + t3+t4+t5+t6;
	if(ec){
		return std::make_tuple(true, t1,t2,t3/ct3,t4/ct4,t5/ct5,t6,tott);
	}return std::make_tuple(false, t1,t2,t3/ct3,t4/ct4,t5/ct5,t6,tott);
}
    
    
    
//ULTRA SUBSET SUM


/* Returns true if there is a subset of set[] with sum equal to t */
std::tuple<bool,int> isSubsetSumUW(std::vector<int>& set,int t, int t1, int t2, int t3, int t4, int t5, int t6){
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	int tott = 0;
	
	begin = std::chrono::steady_clock::now();
	int c,i;
	
	end = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
	//T1
	unsigned int w = UltraWord::WORD_SIZE;  //ultra wide word
	
	tott = tott + t1;
	begin = std::chrono::steady_clock::now();
	
	unsigned int wordsneeded = ceil(double(t+1)/w);
	unsigned int elements = set.size()+1;
	int es,ss,ai,j,k,x;
	
	end = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();

	//T2
	//Create table
	std::vector<std::vector<UltraWord>> table(elements, std::vector<UltraWord>(wordsneeded));
	
	//Initialize first row 
	table[0][0] = (unsigned long long int)1;
	table[0][0] = table[0][0]<<(w-1);
	
	int alength = table.at(0).size();
	
	tott = tott + t2;
	
	begin = std::chrono::steady_clock::now();
	//Fill the table in bottom up manner
	for(c=1;c<elements;c++){
		x = set.at(c-1);
		
		end = std::chrono::steady_clock::now();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		
		//T3
		tott = tott + t3;
		std::vector<UltraWord> orig = table.at(c-1);
		std::vector<UltraWord> aux(alength);
		
		UltraWord aux1;
		UltraWord aux2;
		
		begin = std::chrono::steady_clock::now();
		int bts = floor(x/w);
		int split = x%w;
		j = bts;
		k = 0;
		while(j<alength){
			end = std::chrono::steady_clock::now();
			tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
			//T4
			tott = tott + t4;
			aux1 = orig.at(k)>>split;
			aux.at(j) = aux1|aux2;
			aux2 = orig[k]<<(w-split);
			begin = std::chrono::steady_clock::now();
			j++;k++;
		}
		
		end = std::chrono::steady_clock::now();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		
		begin = std::chrono::steady_clock::now();
		
		for(i=0;i<wordsneeded;i++){
			end = std::chrono::steady_clock::now();
			tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
			//T5
			tott = tott + t5;
			table.at(c).at(i) = table.at(c-1).at(i)|aux.at(i);
			begin = std::chrono::steady_clock::now();
		}
	}
	end = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();

     //T6
     tott = tott + t6;
	UltraWord one;
	one =1;
	UltraWord aux = (table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1));
	bool ec = (aux&one)==one;
	if(ec){
		return std::make_tuple(true,tott);
	}return std::make_tuple(false,tott);
	

}    

void clearCaches(){
	/*const int size = 20*1024*1024; // Allocate 20M. Set much larger then L2
	char *c = (char *)malloc(size);
	for (int i = 0; i < 0xffff; i++){
		for (int j = 0; j < size; j++){
			c[j] = i*j;
		}
	}*/
	
	//sync();

	std::ofstream ofs("/proc/sys/vm/drop_caches");
	ofs << "3" << std::endl;
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
     
     
     clearCaches();
     
     
     auto result = isSubsetSum(set,sum);
     
     if(std::get<0>(result)){
			printf("\nFound a subset with given sum\n");
			printf("t1 = %d\n",std::get<1>(result));
			printf("t2 = %d\n",std::get<2>(result));
			printf("t3 = %d\n",std::get<3>(result));
			printf("t4 = %d\n",std::get<4>(result));
			printf("t5 = %d\n",std::get<5>(result));
			printf("t6 = %d\n",std::get<6>(result));
			printf("tot = %d\n",std::get<7>(result));
		}else{
			printf("\nNo subset with given sum\n");
			printf("tott = %d\n",std::get<6>(result));
		}
		
		
	clearCaches();
		
	 auto UWresult = isSubsetSumUW(set,sum,std::get<1>(result),std::get<2>(result),std::get<3>(result),std::get<4>(result),std::get<5>(result),std::get<6>(result));
	 //bool UWresult = isSubsetSumUW(set,sum);
     
     if(std::get<0>(UWresult)){
		 printf("\nUW Found a subset with given sum\n");
		 printf("UW tot = %d\n",std::get<1>(UWresult));
	 }else{
		 printf("\nUW No subset with given sum\n");
		 printf("UW tot = %d\n",std::get<1>(UWresult));
	 }
}
