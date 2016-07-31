#include <iostream>
#include <chrono>
//g++ timetest.cpp -o timetest -std=c++11

void func(){
	//count lots
	int i;
	int s;
	for(i=0;i<16000; i++){
		s = i;
	}
}

int main(){
	int i = 5; 
	int j = 4;
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
int k = i+j;
std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
}
