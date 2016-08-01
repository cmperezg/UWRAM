    #include <math.h>
    #include <cstdio>
    #include <vector>
     //compile = g++ -o redss -g redss.cpp -std=c++11
    // get bit #bitno from num. 0 is most significant.
    unsigned int getbit(unsigned int num, int bitno){
     
        unsigned int w = sizeof(int)*8;  //for regular word.
        int shiftno = w-bitno-1;
        unsigned int mask = 1<<shiftno;
        unsigned int maskedn = num&mask;
        unsigned int thebit = maskedn>>shiftno;
        return thebit;
    }
     
    /* No boundary array right shift */
    std::vector<int> nbars(std::vector<unsigned int>& orig, unsigned int x){
     
        int alength = orig.size();
        unsigned int b_s = sizeof(int)*8;
        std::vector<int> shifted(alength);
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
            aux1 = orig.at(j)>>split;
            shifted.at(i) = aux1|aux2;
            aux2 = orig[j]<<(b_s-split);
            i++;j++;
        }
        return shifted;
    }
     
    /* Returns true if there is a subset of set[] with sum equal to t */
    bool isSubsetSum(std::vector<int>& set, int t){
        unsigned int w = sizeof(int)*8;  //for regular word.
        unsigned int wordsneeded = ceil(double(t+1)/w);
        unsigned int elements = set.size()+1;
        //Create table
        printf("sizing = elem, wn = %d,%d\n",elements,wordsneeded);
        std::vector<std::vector<unsigned int>> table(elements, std::vector<unsigned>(wordsneeded));
        int c,i;
        //Initialize first row
        for(i=0;i<wordsneeded;i++){
            table.at(0).at(i) = 0;
        }
        table[0][0] = 1<<(w-1);
        //Fill the table in bottom up manner
        int es,ss,ai;
        for(c=1;c<elements; c++){ //<= ??
     
            std::vector<int> aux = nbars(table.at(c-1),set.at(c-1));
            for(i=0;i<wordsneeded;i++){
				printf("c,i = %d,%d\n",c,i);
                table.at(c).at(i) = table.at(c-1).at(i)|(unsigned)aux.at(i);
            }
            }
     
        if((table[elements-1][wordsneeded-1]>>((w*wordsneeded)-t-1))&1 ==1){//problem is here??

     
             return true;
         }return false;
    }
     
     
    int main(){
     
        std::vector<int> set = {81,80,43,40,30,26,12,11,9};
        //int sum = 63;
        int sum = 100;
        int n = set.size();
        if (isSubsetSum(set,sum) == true)
         printf("\nFound a subset with given sum\n");
      else
         printf("\nNo subset with given sum\n");
      return 0;
    }
