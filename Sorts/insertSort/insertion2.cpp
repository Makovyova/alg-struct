#include <iostream>
#include <algorithm>
#include <utility>
//#include <string view>

int main() {
	int n;
	int x[10];
	
	std::cout << "N="; std::cin >> n;
	// Write the sorted array
	std::cout << "Write array: ";
	for (int i = 0; i < n; i++) {
		std::cin >> x[i];
	}
	std::cout << std::endl;


	
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && x[j - 1] > x[j]; j--) // пока j>0 и элемент j-1 > j, x-массив int
			std::swap(x[j - 1], x[j]);        // меняем местами элементы j и j-1

	// Print the sorted array
	std::cout << "Sorted array: ";
	for (int i = 0; i < n; i++) {
		std::cout << x[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}