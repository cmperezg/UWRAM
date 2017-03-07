#include <iostream>
#include <thread>
#include <list>

//compile: g++ -g parbmh.cpp -o parbmh -pthread -std=c++11


  
static const int cores = 8; //number of cores available 
  
//This function will be called from a thread
  
void call_from_thread(int tid) {
	std::cout << "Launched by thread " << tid << std::endl;
	for(int i=0; i<1000000000; i++){
		int j = i+i*i;
	}
	std::cout<<"thread " << tid << " finished" << std::endl;
}

//parallel bmh (disjoint). splits text evenly over cores with an overlap of pattern length -1
//each segment is processed separately by function bmh_t
std::list<int> parbmh(std::string text, std::string pat){
	std::list<int> res;
	int strlen = text.size();
	std::list<std::string> chunks;
	int chunksize = floor((float)strlen/(float)cores)
	for(int c = 0; c<cores; c++){
	}
	return res;
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
