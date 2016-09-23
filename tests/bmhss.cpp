#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;
int offs = 97;

void bmh(string text, string pat){
	int patlen = pat.size();
	int strlen = text.size();
	int alphalen = 26;
	int delta12[alphalen];
	int i;
	for(i=0;i<alphalen;i++){
		delta12[i] = patlen;
	}
	for(i=0;i<patlen;i++){
		delta12[pat.at(i)-offs] = patlen -i;
	}
	/*for(i=0;i<alphalen;i++){
		printf("delta12[%d]: %d\n",i,delta12[i]);
	}*/
	char lastch = pat.at(patlen-1);
	i = patlen-1;
	while(i<strlen){
		char ch = text.at(i);
		if(ch==lastch){
			if(pat.compare(text.substr(i-patlen,i))==0){
				printf("pattern at: %d\n",i-patlen);
				return;
			}
			i = i+delta12[ch-offs];
		}
		
	}return;
}

int main(){
	
	//string tests
	string T = "abcbaabbcabacc";
	string P = "abac";
	cout << "length: " << T.size() << "\n";
	string sub = T.substr(7);
	cout << sub << "\n";
	cout << T.at(8) << "\n";
	
	bmh(T,P);
	
	/*
	int i;
	char alpha[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	for(i=0;i<26;i++){
		printf("%c = %d\n",alpha[i],alpha[i]-offs);
	}
	* */
}
