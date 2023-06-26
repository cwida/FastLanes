#include <cstdint>
#include <iostream>

namespace generator {
template <typename T>
static void randomList(int m, int n, T* arr) {

	// Create an array of size m where
	// every element is initialized to 0
	for (int i = 0; i < n; ++i) {
		arr[i] = 0;
	}
	// To make the sum of the final list as n
	for (int i = 0; i < n - m; i++) {

		// Increment any random element
		// from the array by 1
		arr[rand() % m]++;
	}
}

template <typename T>
static void generate_rle_data(int n, T* value, T* length) {
	// Set the run-values to 0,1,..., n
	for (int i = 0; i < 1024; i++) {
		value[i]  = i;
		length[i] = 0;
	}
	randomList(n, 1024, length);
}
} // namespace generator
