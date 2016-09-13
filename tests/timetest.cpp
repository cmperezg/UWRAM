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
int tott=0;
int k = 8;
int i = 5; 
int j = 4;
std::chrono::steady_clock::time_point begin;
std::chrono::steady_clock::time_point end;
	
begin = std::chrono::steady_clock::now();
k = i+j;
k = k++;
k=k/2 + i;
k = k*j;
end= std::chrono::steady_clock::now();
tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();

printf("con test: %d\n",tott);

tott = 0;
i = 5; 
j = 4;
k = 8;
begin = std::chrono::steady_clock::now();
k = i+j;
k = k++;
end= std::chrono::steady_clock::now();
tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
begin = std::chrono::steady_clock::now();
k=k/2 + i;
k = k*j;
end= std::chrono::steady_clock::now();
tott = tott+std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
printf("noncon test: %d\n",tott);




}
