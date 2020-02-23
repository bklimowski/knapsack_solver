//============================================================================
// Name        : knapsack_solver.cpp
// Author      : BK
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

std::mt19937 mt_engine(137);
std::uniform_real_distribution<> uniform_0_1(0, 1);

template <typename A>
void print_vector(std::vector<A> v) {
	for (A ii: v) {
		std::cout << ii << " ";
	}
	std::cout << std::endl;
}

void transfer_random_element(std::vector<int>& V1,
                             std::vector<int>& V2) {
    std::uniform_int_distribution<> unif(0, V1.size() - 1);
    int random_element = unif(mt_engine);
    V2.push_back(V1[random_element]);
    V1.erase(V1.begin() + random_element);
}

float sum_vector(std::vector<float> values, std::vector<int> idx){
	float sum = 0;
	for (int ii: idx) {
		sum += values[ii];
	}
	return(sum);
}

struct knapsack_problem {
	std::vector<float> weights;
	std::vector<float> values;
	float max_weight;
} knapsack;



std::vector<int> sa_knapsack_solver(knapsack_problem knapsack,
									float beta, int trials){

	std::vector<int> avilable_items, current_solution,
					 tmp_solution, best_solution, proposition;

	int n_items = knapsack.values.size();
	for( int i = 0; i <= n_items; i++ )
		avilable_items.push_back(i);


	float current_weight = 0.0, current_value = 0,
		  tmp_value = 0, best_value = 0, transition_prob;

	for (int ii = 0; ii < trials; ++ii) {

		transfer_random_element(avilable_items, proposition);
		while((current_weight + knapsack.weights[proposition[0]]) > knapsack.max_weight) {
			transfer_random_element(tmp_solution, avilable_items);
			current_weight = sum_vector(knapsack.weights, tmp_solution);
		}
		tmp_solution.push_back(proposition[0]);
		tmp_value = sum_vector(knapsack.values, tmp_solution);
		transition_prob = std::exp(beta*(tmp_value - current_value));

		if (transition_prob > uniform_0_1(mt_engine)) {
			current_solution = tmp_solution;
			current_weight = sum_vector(knapsack.weights, current_solution);
			proposition.erase(proposition.begin());
		}

		if (tmp_value > best_value) {
			best_solution = tmp_solution;
			best_value = tmp_value;
		}
	}

	return best_solution;

}

int main() {



	knapsack.max_weight = 200;

	std::gamma_distribution<> gamma(2, 2);

	for( int i = 0; i <= 10000; i++ ) {
		knapsack.values.push_back(gamma(mt_engine));
		knapsack.weights.push_back(gamma(mt_engine));
	};

	auto result = sa_knapsack_solver(knapsack, 0.5, 100000);

	std::cout << "Hello world" << std::endl;
	print_vector(result);

	std::cout << sum_vector(knapsack.values, result) << std::endl;
	std::cout << sum_vector(knapsack.weights, result) << std::endl;

	return 0;
}
