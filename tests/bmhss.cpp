#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>

//compile: g++ bmhss.cpp  -o bmhss -std=c++11

using namespace std;
void bmh(string text, string pat){
	int patlen = pat.size();
	long long int strlen = text.size();
	printf("strlen: %lld\n",strlen);
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
	/*for(i=0;i<alphalen;i++){
		printf("delta12[%d]: %d\n",i,delta12[i]);
	}*/
	//printf("lastch: %c\n",lastch);
	i = patlen-1;
	//printf("i: %d, strlen: %d\n",i,strlen);
	
	while(i<strlen){
		//printf("i: %lld\n",i);
		char ch = text.at(i);
		//printf("i: %d, ch: %c\n",i,ch);
		if(ch==lastch){
			//printf("doesthiseverhappen\n");
			//cout << "substr: " << text.substr(i-patlen+1,patlen)<< "\n";
			//printf("comparison: %d \n",(pat.compare(text.substr(i-patlen+1,patlen))));
			if((pat.compare(text.substr(i-patlen+1,patlen)))==0){
				printf("pattern at: %lld\n",i-patlen+1);
				//return;
			}
			
		}
		//printf("ch: %d, i: %lld, del[ch]: %d\n",ch,i,delta12[ch]);
		i = i+delta12[ch];
		
	}return;
}

int main(){

	ifstream infile {"lidata100.txt"};
	string fst{istreambuf_iterator<char>(infile),istreambuf_iterator<char>()};
	
	transform(fst.begin(),fst.end(),fst.begin(),::tolower);
	
	//cout<<fst<<"\n";
	
	string P = "quisque";
	//string P = "elementum risus";
	bmh(fst,P);

}
