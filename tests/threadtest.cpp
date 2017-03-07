#include <iostream>
#include <thread>

//compile: g++ -g threadtest.cpp -o threadtest -pthread -std=c++11


  
static const int num_threads = 8;
  
//This function will be called from a thread
  
void call_from_thread(int tid) {
	std::cout << "Launched by thread " << tid << std::endl;
	for(int i=0; i<1000000000; i++){
		int j = i+i*i;
	}
	std::cout<<"thread " << tid << " finished" << std::endl;
}
 
int main() {
    std::thread t[num_threads]; 
	//Launch a group of threads
	for (int i = 0; i < num_threads; ++i) {
		t[i] = std::thread(call_from_thread, i);
	}
	
	std::cout << "Launched from the main\n";
 
	//Join the threads with the main thread
	for (int i = 0; i < num_threads; ++i) {
		t[i].join();
	}
	
	return 0;
}
