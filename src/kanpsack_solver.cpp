//============================================================================
// Name        : kanpsack_solver.cpp
// Author      : Bartlomiej Klimowski
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * Stuff to do:
 * 1. Generate values from normal distribution
 * 2. Sorting enumerated list
 * 3. Drop one element at random
 * 4. Sum list elements
 * 5. Set operators
 * 6. Create range of values
 * 7. exponent and uniform draw
 */

#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <algorithm>

template <typename T>
std::vector<size_t> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<size_t> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(),
       [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  return idx;
}


std::vector<double> draw_from_half_normdist(int n_samples, float mean, float sd){

	std::vector<double> g1;

	std::random_device rd {};
	std::mt19937 mt(rd());
	std::normal_distribution<double> dist(mean, sd);

    for (int i = 1; i <= n_samples; i++)
        g1.push_back(std::abs(dist(mt)));

    return g1;
}

int main() {

	std::vector<double> half_normal_weights = draw_from_half_normdist(1000, 0, 1);
	std::vector<double> half_normal_values = draw_from_half_normdist(1000, 0, 2);

	std::vector<double> weights_values_ratios;

	for (unsigned ii = 1; ii < half_normal_weights.size(); ++ii) {
		weights_values_ratios.push_back(half_normal_weights[ii]/half_normal_values[ii]);
	};

	for(auto &value: half_normal_weights) {
		std::cout << value;
	}

	std::cout << std::endl;

	for(auto &value: half_normal_values) {
		std::cout << value;
	}

	std::cout << std::endl;

	for(auto &value: weights_values_ratios) {
		std::cout << value;
	}

	std::cout << std::endl;

	for (auto i: sort_indexes(half_normal_weights)) {
	  std::cout << i << std::endl;
	}

}

