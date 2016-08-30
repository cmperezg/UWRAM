    #include <math.h>
    #include <cstdio>
    #include <vector>
    #include <chrono>
    #include <tuple>
    #include "ultraword.h"
    
    
//compile = g++ -o timed_wss -g timed_wss.cpp -std=c++11
//compile: g++ timed_wss.cpp ultraword.cpp -o timed_wss -std=c++11
    
    int initnb=0,shiftnb=0,initss=0,assigss=0,ecss=0,fulltime=0;
    int cinitnb=0,cshiftnb=0,cassigss=0;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::steady_clock::time_point tbegin;
    std::chrono::steady_clock::time_point tend;
    int tott=0;
    
    
//WORD SUBSET SUM
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
     
    /* No boundary array right shift */
    std::vector<int> nbars(std::vector<unsigned int>& orig, unsigned int x){
		tbegin = std::chrono::steady_clock::now();
		int i;

		tend = std::chrono::steady_clock::now();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (tend - tbegin).count();
		
		begin = std::chrono::steady_clock::now();
        int alength = orig.size();
        unsigned int b_s = sizeof(int)*8;
        std::vector<int> shifted(alength);
     
        unsigned int aux1 = 0;
        unsigned int aux2 = 0;
		
		end = std::chrono::steady_clock::now();
		initnb = initnb + std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		cinitnb++;
		tbegin = std::chrono::steady_clock::now();
        int bts = floor(x/b_s);
        int split = x%b_s;
        i = bts;
        int j = 0;
        while(i<alength){
			tend = std::chrono::steady_clock::now();
			tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (tend - tbegin).count();
			begin = std::chrono::steady_clock::now();
            aux1 = orig.at(j)>>split;
            shifted.at(i) = aux1|aux2;
            aux2 = orig[j]<<(b_s-split);
            end = std::chrono::steady_clock::now();
            shiftnb = shiftnb + std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
            cshiftnb++;
            tbegin = std::chrono::steady_clock::now();
            i++;j++;
        }
        return shifted;
    }
     
    /* Returns true if there is a subset of set[] with sum equal to t */
	std::tuple<bool,int,int,int,int,int,int> isSubsetSum(std::vector<int>& set, int t){	
		tbegin = std::chrono::steady_clock::now();
		int c,i;
		tend = std::chrono::steady_clock::now();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (tend - tbegin).count();
		
		begin = std::chrono::steady_clock::now();
        unsigned int w = sizeof(int)*8;  //for regular word.
        unsigned int wordsneeded = ceil(double(t+1)/w);
        unsigned int elements = set.size()+1;
        //Create table
        std::vector<std::vector<unsigned int>> table(elements, std::vector<unsigned>(wordsneeded));
        //Initialize first row
        table[0][0] = 1<<(w-1);
        end = std::chrono::steady_clock::now();
		initss = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		tbegin = std::chrono::steady_clock::now();
        //Fill the table in bottom up manner
        int es,ss,ai;
        tend = std::chrono::steady_clock::now();
        tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (tend - tbegin).count();
        for(c=1;c<elements; c++){
			 //nbars measurement
            std::vector<int> aux = nbars(table.at(c-1),set.at(c-1));
            
            for(i=0;i<wordsneeded;i++){
				begin = std::chrono::steady_clock::now();
                table.at(c).at(i) = table.at(c-1).at(i)|(unsigned)aux.at(i);
                end = std::chrono::steady_clock::now();
                assigss = assigss+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
                tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
                cassigss++;
            }
        }
		begin = std::chrono::steady_clock::now();
		bool ec = (table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1;
		end = std::chrono::steady_clock::now();
		ecss = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();

        if(ec){
             return std::make_tuple(true,initnb/cinitnb,shiftnb/cshiftnb,initss,assigss/cassigss,ecss,tott);
         }return std::make_tuple(false,initnb/cinitnb,shiftnb/cshiftnb,initss,assigss/cassigss,ecss,tott);
//return false;
    }
    
    
    
    
    
    
//ULTRA SUBSET SUM

/* No boundary array right shift (across UltraWords) */
std::vector<UltraWord> nbars(std::vector<UltraWord>& orig, unsigned int x, int initnbll, int shiftnbll){
	tbegin = std::chrono::steady_clock::now();
	int i;
	tend = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (tend - tbegin).count();
	int alength = orig.size();
	unsigned int b_s = UltraWord::WORD_SIZE;
	std::vector<UltraWord> shifted(alength);
	

	UltraWord aux1;
    UltraWord aux2;
     tott = tott +initnbll;
    tbegin = std::chrono::steady_clock::now();
    int bts = floor(x/b_s);
    int split = x%b_s;
    i = bts;
	int j = 0;
    while(i<alength){
		tend = std::chrono::steady_clock::now();
		tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (tend - tbegin).count();
		aux1 = orig.at(j)>>split;
		shifted.at(i) = aux1|aux2;
		aux2 = orig[j]<<(b_s-split);
		tott = tott + shiftnbll;
		tbegin = std::chrono::steady_clock::now();
		i++;j++;
	}
	return shifted;
}

/* Returns true if there is a subset of set[] with sum equal to t */
std::tuple<bool,int> isSubsetSum(std::vector<int>& set,int t,int initnbl,int shiftnbl,int initssl,int assigssl,int ecssl){
	tbegin = std::chrono::steady_clock::now();
	int c,i;
	tend = std::chrono::steady_clock::now();
	tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (tend - tbegin).count();
	//init
	unsigned int w = UltraWord::WORD_SIZE;  //ultra wide word
	unsigned int wordsneeded = ceil(double(t+1)/w);
	unsigned int elements = set.size()+1;
	//printf("W: %d\n",w);
	//Create table
	std::vector<std::vector<UltraWord>> table(elements, std::vector<UltraWord>(wordsneeded));
	
	//Initialize first row 
	table[0][0] = 1;
	table[0][0] = table[0][0]<<(w-1);
	tott = tott + initssl;
	tbegin = std::chrono::steady_clock::now();
	//Fill the table in bottom up manner
	int es,ss,ai;
	tend = std::chrono::steady_clock::now();
    tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (tend - tbegin).count();
	for(c=1;c<elements;c++){
		//tbegin = std::chrono::steady_clock::now();
		std::vector<UltraWord> aux = nbars(table.at(c-1),set.at(c-1),initnbl,shiftnbl);
		for(i=0;i<wordsneeded;i++){
			table.at(c).at(i) = table.at(c-1).at(i)|aux.at(i);
			tott = tott + assigssl;
		}
	}

     
	UltraWord one;
	one =1;
	UltraWord aux = (table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1));
	tott = tott+ecssl;
	bool ec = (aux&one)==one;
	if(ec){
		return std::make_tuple(true,tott);
	}return std::make_tuple(false,tott);
	

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

        int n = set.size();
        auto result = isSubsetSum(set,sum);
        
        if(std::get<0>(result)){
			printf("\nFound a subset with given sum\n");
			printf("initnb = %d\n",std::get<1>(result));
			printf("shiftnb = %d\n",std::get<2>(result));
			printf("initss = %d\n",std::get<3>(result));
			printf("assigss = %d\n",std::get<4>(result));
			printf("ecss = %d\n",std::get<5>(result));
			printf("tott = %d\n",std::get<6>(result));
		}else{
			printf("\nNo subset with given sum\n");
			printf("tott = %d\n",std::get<6>(result));
		}
       
       auto result2 = isSubsetSum(set,sum,std::get<1>(result),std::get<2>(result),std::get<3>(result),std::get<4>(result),std::get<5>(result));
       if(std::get<0>(result2)){
			printf("\n UW Found a subset with given sum\n");
			printf("tott = %d\n",std::get<1>(result2));
		}else{
			printf("\n UW No subset with given sum\n");
			printf("tott = %d\n",std::get<1>(result2));
		}
      return 0;
    }
