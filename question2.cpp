//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, 
//make sure that sum=EXPECTED_SUM after using threads
//please explain the changes you made and what new aspects you had to deal with 
//when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

//My explanation:
//In parallel program the threads are running together and the danger is that it can arise a race condition - 
//that beacuse both functions are access the same global sum variable and change it
//so I defined a function g_lock() to avoid this situation, by using a global mutex for both threads
//so one thread only can access the sum variable at any given moment

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex> 

constexpr size_t ITERATIONS = 1000*1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

size_t sum = 0;

//make up a lock for output stream 
auto g_lock() 
{ 
    static std::mutex m; // a global living mutyex 
    return std::unique_lock<decltype(m)>(m); // RAII based lock 
} 

void operation1(size_t arg) {
	std::cout << "Performing operation1" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		auto lk = g_lock(); //keep output locked up to } 
		sum += (arg+i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work 
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::cout << "Performing operation2" << std::endl;
	for (size_t i = 0; i < ITERATIONS; i++) {
		auto lk = g_lock();
		sum += (arg*i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}


int main(int argc, char** argv)
{
	auto start = std::chrono::steady_clock::now();
	std::thread t1(operation1, OP1_PARAM);
	std::thread t2(operation2, OP2_PARAM);

	t1.join();
	t2.join();
	
	//operation1(OP1_PARAM);
	//operation2(OP2_PARAM);
	auto end = std::chrono::steady_clock::now();

	std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "Result:  " << sum <<  ", " <<(sum == EXPECTED_SUM ? "success" : "failure!")<< std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}
