#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include "ultraword.h"

//compile: g++ uwclasstest.cpp ultraword.cpp -o uwclasstest -std=c++11

using namespace std;

void bmh(string T, string P){
	//preprocessing
	int n = P.size();
	long long int m = T.size();
	
	int alphalen = 125;
	int jump[alphalen];
}
