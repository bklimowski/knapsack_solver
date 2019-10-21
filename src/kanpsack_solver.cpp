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

//template <typename T>
//std::vector<size_t> sort_indexes(const std::vector<T> &v) {
//
//  // initialize original index locations
//  std::vector<size_t> idx(v.size());
//  std::iota(idx.begin(), idx.end(), 0);
//
//  // sort indexes based on comparing values in v
//  std::sort(idx.begin(), idx.end(),
//       [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});
//
//  return idx;
//}

template <typename distribution>
std::vector<double> draw_from_dist(int n_samples, distribution dist){

	std::vector<double> g1;

	std::random_device rd {};
	std::mt19937 mt(rd());

    for (int i = 1; i <= n_samples; i++)
        g1.push_back(std::abs(dist(mt)));

    return g1;
}

int main() {

	std::normal_distribution<double> norm_dist(0.1, 1.0);
	std::vector<double> normal_draws = draw_from_dist(100, norm_dist);

	std::cout << normal_draws[1] << std::endl;

}

