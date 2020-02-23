#include <iostream>
#include <vector>
#include <random>
#include <cmath>
std::mt19937 mt_engine(137);

void program_welcome(){
	std::cout << "+============================+" << std::endl;
	std::cout << "+ 0-1 KNAPSACK PROBLEM SOLVER+" << std::endl;
	std::cout << "+============================+" << std::endl;
	std::cout << "+  WITH SIMULATED ANNEALING  +" << std::endl;
	std::cout << "+============================+" << std::endl;
	std::cout << "+AUTHOR: BARTLOMIEJ KLIMOWSKI+" << std::endl;
	std::cout << "+============================+" << std::endl;
	std::cout << std::endl;
}

struct knapsack_problem {
	std::vector<float> weights;
	std::vector<float> values;
	float max_weight;
};

void transfer_random_element(std::vector<int>& V1, std::vector<int>& V2) {
	std::uniform_int_distribution<> unif(0, V1.size() - 1);
	int random_element = unif(mt_engine);
	V2.push_back(V1[random_element]);
	V1.erase(V1.begin() + random_element);
}

float sum_vector(std::vector<float> values, std::vector<int> idx){
	float sum = 0;
	for (int ii: idx) {sum += values[ii];}
	return(sum);
}

std::vector<int> sa_knapsack_solver(knapsack_problem knapsack, float beta, int trials){
	std::vector<int> avilable_items, current_solution, tmp_solution, best_solution, proposition;
	std::uniform_real_distribution<> uniform_0_1(0, 1);
	int n_items = knapsack.values.size();
	for( int ii = 0; ii < n_items - 1; ii++)
		avilable_items.push_back(ii);
	float current_weight = 0.0, current_value = 0, tmp_value = 0, best_value = 0, transition_prob;
	if(sum_vector(knapsack.weights, avilable_items) < knapsack.max_weight){
		return avilable_items;
	}
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

knapsack_problem random_knapsack(){
	knapsack_problem knapsack;
	int n_elements;
	std::cout << "Please provide max weight:" << std::endl;
	std::cin >> knapsack.max_weight;
	std::cout << "Please provide number of elements" << std::endl;
	std::cin >> n_elements;
	std::gamma_distribution<> gamma(0.1, 10);
	for( int ii = 0; ii <= n_elements; ii++ ) {
		knapsack.values.push_back(gamma(mt_engine));
		knapsack.weights.push_back(gamma(mt_engine));
	};
	return knapsack;
}

void knapsack_menu() {
	knapsack_problem knapsack;
	int option, n_trials;
	float beta;
	std::vector<int> result;
	std::cout << "Choose option number:" << std::endl;
	std::cout << "1. Random generated problem" << std::endl;
	std::cout << "2. Exit" << std::endl;
	std::cout << std::endl;
	std::cin >> option;
	switch(option) {
	case 1:
		knapsack = random_knapsack();
		std::cout << "Insert number of trials:" << std::endl;
		std::cin >> n_trials;
		std::cout << "Insert beta parameter:" << std::endl;
		std::cin >> beta;
		result = sa_knapsack_solver(knapsack, beta, n_trials);
		std::cout << "-----------" << std::endl;
		std::cout << "RESULTS:" << std::endl;
		std::cout << "Value:" << std::endl;
		std::cout << sum_vector(knapsack.values, result) << std::endl;
		std::cout << "Weight:" << std::endl;
		std::cout << sum_vector(knapsack.weights, result) << std::endl;
		std::cout << "Elements:" << std::endl;
		for (int ii: result) {std::cout << ii << " ";}
		std::cout << std::endl;
		std::cout << "-----------" << std::endl;
		break;
	case 2:
		exit(0);
	default:
		std::cout<<"Invalid input"<<std::endl;
		break;
	}

	std::cout << std::endl;
}

int main() {
	program_welcome();
	while(true) {
		knapsack_menu();
	}
	return 0;
}
