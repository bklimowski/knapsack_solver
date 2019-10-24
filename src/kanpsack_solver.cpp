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

#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <unistd.h>

template <typename T>
std::vector<int> sort_indexes(const std::vector<T> &v) {

  // initialize original index locations
  std::vector<int> idx(v.size());
  std::iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  std::sort(idx.begin(), idx.end(),
       [&v](int i1, int i2) {return v[i1] < v[i2];});

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

template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n;

    std::vector<T> vec(first, last);
    return vec;
}

template<typename T1, typename T2>
std::vector<double> calc_ratios(std::vector<T1> vec1, std::vector<T2> vec2) {

	std::vector<double> ratios;

	for (auto ii = 0; ii < vec1.size(); ii++) {
		ratios.push_back(vec1[ii]/vec2[ii]);
	}

	return ratios;

}

template<typename T1, typename T2, typename T3>
std::vector<int> initialize_naive_solution(std::vector<T1> weights, std::vector<T2> values, T3 capacity) {

//	std::vector<int> naive_solution;
	std::vector<double> ratios = calc_ratios(weights, values);
	std::vector<int> sorted_ratios = sort_indexes(ratios);


	int total_weigth { 0 };
	int n_top_items { 0 };

	while(total_weigth <= capacity) {
		total_weigth += weights[sorted_ratios[n_top_items]];
		//std::cout <<  weights[sorted_ratios[n_top_items]] << std::endl;
		n_top_items++;
	}

	std::vector<int> naive_solution = slice(sorted_ratios, 0, n_top_items);

	return naive_solution;
}

std::vector<int> range(int upper_limit) {
	std::vector<int> range_vector;

	for (int ii = 0; ii < upper_limit; ii++) {
		range_vector.push_back(ii);
	}

	return range_vector;
}

template<typename T>
std::vector<T> set_difference(std::vector<T> &v1, std::vector<T> &v2){

	std::vector<T> v3;

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::inserter(v3, v3.begin()));
    return v3;
}

template<typename T>
T draw_element(std::vector<T> &v) {

	std::random_device rd {};
	std::mt19937 mt(rd());

	std::uniform_int_distribution<int> uniform(0, v.size());
	auto sample = draw_from_dist(1, uniform, mt);
	return v[sample[0]];
}


int main() {

	program_intro();

//	int capacity { 10 };
//
//	std::random_device rd {};
//	std::mt19937 mt(rd());
//	std::poisson_distribution<int> pois1 { 10 };
//	auto weights = draw_from_dist(10, pois1, mt);
//	std::poisson_distribution<int> pois2 { 20 };
//	auto values = draw_from_dist(10, pois2, mt);
//	print_vector(slice(weights,0,2));
//
//	std::vector<int> naive_solution = initialize_naive_solution(weights, values, capacity);
//
//	print_vector(weights);
//	print_vector(values);
//	print_vector(naive_solution);

	auto test = range(10);
	auto slice_v = slice(test, 0, 5);
	print_vector(test);
	print_vector(slice_v);

	auto a = set_difference(test, slice_v);

	print_vector(a);
	std::cout << draw_element(test);
	std::cout << draw_element(test);
	return 0;
}




