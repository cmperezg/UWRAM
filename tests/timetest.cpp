#include <iostream>
#include <chrono>

void func(){
	//count lots
	int i;
	int s;
	for(i=0;i<89972; i++){
		s = i;
	}
}

int main(){
	
std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
func();
std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
}
