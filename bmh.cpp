#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <list>

//compile: g++ bmh.cpp  -o bmh -std=c++11

std::list<int> bmh(std::string text, std::string pat){
	std::list<int> res;
	int patlen = pat.size();
	long long int strlen = text.size();
	//printf("strlen: %lld\n",strlen);
	int alphalen = 128; //ascii
	int delta12[alphalen];
	int j;
	for(j=0;j<alphalen;j++){
		delta12[j] = patlen;
	}
	for(j=0;j<patlen;j++){
		delta12[pat.at(j)] = patlen -j-1;
	}
	
	char lastch = pat.at(patlen-1);
	delta12[lastch] = patlen;
	
	long long int i;

	i = patlen-1;
	
	while(i<strlen){
		//printf("i: %lld\n",i);
		char ch = text.at(i);
		if(ch==lastch){
			if((pat.compare(text.substr(i-patlen+1,patlen)))==0){
				res.push_back(i-patlen+1);

			}
			
		}
		//printf("ch: %d, i: %lld, del[ch]: %d\n",ch,i,delta12[ch]);
		i = i+delta12[ch];
		
	}return res;
}


void printResults(const std::list<int>& s){
	std::cout<< "found pattern at: ";
	std::list<int>::const_iterator i;
	for(i=s.begin();i!=s.end();++i){
		std::cout<<*i << " ";
	}
	std::cout<< "\n";
}

int main(){

	std::ifstream infile {"lidata10.txt"};
	std::string fst{std::istreambuf_iterator<char>(infile),std::istreambuf_iterator<char>()};
	
	std::transform(fst.begin(),fst.end(),fst.begin(),::tolower);
	
	//cout<<fst<<"\n";
	
	std::string P = "vestibulum";
	printResults(bmh(fst,P));

}
