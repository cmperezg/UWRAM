#include <cstdio>
#include <iostream>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <list>

//compile: g++ -g wcrochperr.cpp -o wcrochperr -std=c++11


std::tuple<int,int> maxsuffaz(std::string x){
	int i = 0;
	int j = 1;
	int k = 1;
	int p = 1;
	int n = x.size();

	while(j+k < n){
		int ap = x.at(i+k);
		int a = x.at(j+k);

		if(a < ap){
			j = j + k;
			k = 1;
			p = j - i;
		}
		if(a == ap){
			if(k = p){
				j = j + p;
				k = 1;
			}else{
				k = k + 1;
			}
		}
		if(a > ap){
			i = j;
			j = i + 1;
			k = 1;
			p = 1;
		}
	}
	return std::make_tuple(i,p); // p is the period, i is the position of the suffix
}


std::tuple<int,int> maxsuffza(std::string x){ //reversed alphabet ordering
	int i = 0;
	int j = 1;
	int k = 1;
	int p = 1;
	int n = x.size();

	while(j+k < n){
		int ap = x.at(i+k);
		int a = x.at(j+k);

		if(a > ap){
			j = j + k;
			k = 1;
			p = j - i;
		}
		if(a == ap){
			if(k = p){
				j = j + p;
				k = 1;
			}else{
				k = k + 1;
			}
		}
		if(a < ap){
			i = j;
			j = i + 1;
			k = 1;
			p = 1;
		}
	}
	return std::make_tuple(i,p); // p is the period, i is the position of the suffix
}

inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

std::list<int> match(std::string x, std::string t){ // x = pattern, t = text
	std::list<int> P;
	int n = x.size();
	std::tuple<int,int> az = maxsuffaz(x);
	std::tuple<int,int> za = maxsuffza(x);

	printf("l1: %d\n",std::get<0>(az));
	printf("l2: %d\n",std::get<0>(za));
	printf("p1: %d\n",std::get<1>(az));
	printf("p2: %d\n",std::get<1>(za));

	int l1 = std::get<0>(az);
	int p1 = std::get<1>(az);
	int l2 = std::get<0>(za);
	int p2 = std::get<1>(za);

	int l; int p;

	if(l1>=l2){
		l = l1;
		p = p1;
	}else{
		l = l2;
		p = p2;
	}

	std::cout << x.substr(l+1,p) << "\n";
	std::cout << x.substr(0,l) << "\n";
	std::cout << "comp: " << ends_with(x.substr(l+1,p),x.substr(0,l))<< "\n" ;

	if(l<(n/2) & ends_with(x.substr(l+1,p),x.substr(0,l))){

		int pos = 0;
		int s = 0;

		while(pos+n <= t.size()){
			int i = std::max(l,s)+1;
			while(i<=n & x.at(i)==t.at(pos+i)){ //FAILS
				i++; //OPT
			}
			if(i<=n){
				pos = pos+ std::max(i-l,s-p+1);
				s = 0;
			}else{
				int j = l;
				while(j>s & x.at(j)==t.at(pos+j)){
					j--; // OPT
				}
				if(j<=s){
					P.push_back(pos);
				}
				pos = pos+p;
				s = n-p;
			}
		}
		return P;

	}else{
		int q = std::max(l, n-l) +1;
		int pos = 0;
		while(pos + n <= t.size()){
			int i = l+1;
			while(i<n & x.at(i)== t.at(pos+i)){
				i++; //OPT
			}
			if(i <= n){
				pos = pos+i -l;
			}else{
				int j = l;
				while(j>0 & x.at(j)==t.at(pos+j)){
					j--; //OPT
				}
				if(j==0){
					P.push_back(pos);
				}
				pos= pos+q;
			}
		}
		return P;
	}

	return P;
}

void print_list(const std::list<int>& s) {
	std::list<int>::const_iterator i;
	for( i = s.begin(); i != s.end(); ++i)
		std::cout << *i << " ";
	std::cout << std::endl;
}

int main(){
	printf("banana ends with nana?: %d\n", ends_with("banana","nana"));

	std::list<int> res = match("nana", "banana");
	print_list(res);

	return 0;
}































