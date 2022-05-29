//Question 1 - basic STL

//Task 1: improve fill_vector and vecOfVec.push_back performance - execution time can be reduced significantly, 
//please explain the changes you made and how they improve
// the application performance.

//Task 2: Implement count_total_elements without using a "visible" for loop

//Task 3: Implement merge_vec_of_vec 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify ELEMENT_COUNT and ITERATIONS and functions fill_vector,count_total_elements and merge_vec_of_vec function signatures  

#include <chrono>
#include <iostream>
#include <vector>

constexpr size_t ELEMENT_COUNT = 1000 * 10000;
constexpr size_t ITERATIONS = 10;

std::vector<uint64_t> fill_vector(size_t elementCount) {
	//TODO: improve function performance
	std::vector<uint64_t> vec(elementCount); 
    //vec.reserve(elementCount);
	//for (size_t i = 0; i < elementCount; i++) {
	//	vec.push_back(i);

    //Some algorithms can take advantage of the exact containter type they are working on, and have better complexity than "manual" loops
    //memset can be faster since it is written in assembler, whereas std::fill is a template function which simply does a loop internally.
	//But for type safety and more readable code std::fill() is better - 
	//and consider memset if a performance optimization is needed at this place in the code.
    size_t i = 0;
    std::fill(vec.begin(), vec.end(), i++); //if using fill initiate vec with size: vec(elementCount)
    //memset(&vec[0], i++, elementCount);
    //}
	return vec;
    
}
/// This function should return the total elements in all of the vectors
size_t count_total_elements(const std::vector<std::vector<uint64_t>>& vecOfVec) {
	return vecOfVec.size() * ELEMENT_COUNT; //TODO: replace with your code
}

/// This function should return a single vector that contain all of the elements of the vectors in vecOfVec
std::vector<uint64_t> merge_vec_of_vec(std::vector<std::vector<uint64_t>>& vecOfVec) {
	std::vector<uint64_t> mergedVec;
	//TODO: Your code here
	size_t total_size{0};
	for(auto const& items: vecOfVec)
		total_size += items.size();
	mergedVec.reserve(total_size);
	for(auto const& items: vecOfVec)
		mergedVec.insert(end(mergedVec), begin(items), end(items));
	return mergedVec;
}

int main(int argc, char** argv)
{
	//Create vector of vectors
	//std::vector<std::vector<uint64_t>> vecOfVec;
	auto start = std::chrono::steady_clock::now();
	//for (size_t i = 0; i < ITERATIONS; i++) {
	std::vector<uint64_t> vec = fill_vector(ELEMENT_COUNT);
		//TODO: improve inserting performance
	//When dimensions are large, the code that was written before (in comment) suffers from potential performance penalties 
	//caused by frequent reallocation of memory by the push_back() function. 
	//This should be used only when vector dimensions are not known in advance.
	std::vector<std::vector<uint64_t>> vecOfVec(ITERATIONS, vec);
	
	//std::fill(vecOfVec.begin(), vecOfVec.end(), vec);
	//	vecOfVec.push_back(vec);
	//}
	auto end = std::chrono::steady_clock::now();
	size_t averageIterationTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / ITERATIONS;
	std::cout << "Average iteration duration in microseconds: " << averageIterationTimeUs << std::endl;
	
	//Count elements
	size_t totalElements = count_total_elements(vecOfVec);
	std::cout << "Total elements in vecOfVec: " << totalElements <<  " " << std::endl;

	//Merge vector of vectors
	std::vector<uint64_t> mergedVec = merge_vec_of_vec(vecOfVec);
	std::cout << "Total elements in merged mergedVec: " << mergedVec.size() << std::endl;

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}
