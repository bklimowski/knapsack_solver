//============================================================================
// Name        : kanpsack_solver.cpp
// Author      : Bartlomiej Klimowski
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * Stuff to do:
 * 1. Generate values from normal distribution - done
 * 2. Sorting enumerated list - done
 * 3. Drop one element at random
 * 4. Sum list elements
 * 5. Set operators
 * 6. Create range of values
 * 7. exponent and uniform draw
 */

/*
 * Implement in R / python
 * Genetic Algorithm
 * Tabu Search
 * Dynamic Programming
 */

#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unistd.h>

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

template <typename A>
void print_vector(std::vector<A> v) {
	for (A ii: v) {
		std::cout << ii << " ";
	}
	std::cout << std::endl;
}

template <typename distribution, typename random_generator>
std::vector<double> draw_from_dist(int n_samples, distribution dist, random_generator rg){

	std::vector<double> draws;
	draws.reserve(n_samples);

    for (int i = 1; i <= n_samples; i++)
    	draws.push_back(fabs(dist(rg)));

    return draws;
}

void program_intro(){
	std::string program_name {"KNAPSACK SOLVER"};
	std::string version {"version 0.1"};
	std::string author {"author: Bartlomiej Klimowski"};

	for (auto ii: program_name) {
		std::cout << ii << " ";
		sleep(0.2);
	}

	for (auto ii: version) {
		std::cout << ii;
		sleep(0.2);
	}

	std::cout << std::endl;

	for (auto ii: author) {
		std::cout << ii;
		sleep(0.2);
	}

	std::cout << std::endl;
}

int main() {

	program_intro();

	int capacity { 10 };

	std::random_device rd {};
	std::mt19937 mt(rd());

	std::normal_distribution<double> norm_dist1(1, 1.0);
	std::vector<double> weigths = draw_from_dist(10, norm_dist1, mt);


	print_vector(weigths);
	auto sorted_indexes = sort_indexes(weigths);
	std::reverse(sorted_indexes.begin(), sorted_indexes.end());
	print_vector(sorted_indexes);

	int total_weigth { 0 };
	int n_top_items { 0 };

	while(total_weigth < capacity) {
		total_weigth += weigths[sorted_indexes[n_top_items]];
		n_top_items++;
		std::cout << n_top_items;
	}

	std::cout << std::endl;

	for (int ii = 0; ii < n_top_items; ++ii) {
		std::cout << sorted_indexes[ii] + 1 << " ";
	}
}


