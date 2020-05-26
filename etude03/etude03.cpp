#include <iostream>
#include <cstdlib>
#include <string>
#include <istream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm> // for reversing vectors
#include <cmath>

using namespace std;

string increment_bitsting(string bitstring);

struct Scenario {
	vector<int> numbers;
	int target_value;
	string order_mode;
	string output; // TODO: change to vector<char>

	Scenario() {
		// init
	}

	// method: given a scenario object and a solution in the form of a bitstring, create the output for the solution
	// if the solution is -1, do the "impossible" output
	// else ...
	void set_solution(vector<char> solution_operators) {
		if (solution_operators[0] == '0') { // impossible
			this->output = order_mode + " " + to_string(target_value) + " impossible";
			return;
		}

		this->output = order_mode + " " + to_string(target_value) + " ";
		for (int i = 0; i < this->numbers.size(); i++) {
			if (i == this->numbers.size() - 1) {
				this->output += to_string(this->numbers[i]);
			}
			else {
				this->output += to_string(this->numbers[i]) + " ";
				char op = solution_operators[i];
				this->output += op;
				this->output += ' ';
			}
		}

	}
};

vector<char> DFS(vector<int> input_numbers, unsigned int level, int partial_sum, vector<char> operators, int target_value) {
	// trim
	if (partial_sum > target_value) {
		vector<char> empty_vec;
		empty_vec.clear();
		return empty_vec;
	}

	// base case: if start_node is a leaf
	if (level == input_numbers.size() - 1) {
		if (partial_sum == target_value) {
			return operators;
		} 
	}
	else {
		level++;
		vector<char> solution;
		vector<char> operators_left = operators, operators_right = operators;

		// left child
		int left_partial_sum = partial_sum + input_numbers[level]; 
		operators_left.push_back('+');
		solution = DFS(input_numbers, level, left_partial_sum, operators_left, target_value);
		if (!solution.empty()) {
			return solution;
		}
	
		// right child
		int right_partial_sum = partial_sum * input_numbers[level];
		operators_right.push_back('*');
		solution = DFS(input_numbers, level, right_partial_sum, operators_right, target_value);
		if (!solution.empty()) {
			return solution;
		}

	}
	// signal that the DFS did not find a valid solution here
	vector<char> empty_vec;
	empty_vec.clear();
	return empty_vec;
}


vector<char> DFSN(vector<int> input_numbers, unsigned int level, pair<int, int> operands, vector<char> operators, int target_value) {
	
	
	// base case: if start_node is a leaf: only additions remain, sum it all up
	if (level == input_numbers.size() - 1) {
		int sum = operands.first + operands.second;

		if (sum == target_value) {
			return operators;
		}
	}
	else {
		// operations to prepare for the next level of the tree
		level++;
		vector<char> solution;
		vector<char> operators_left = operators, operators_right = operators;
		pair<int,int> operands_left = operands, operands_right = operands;

		operands_left = make_pair(operands_left.first + operands_left.second, input_numbers[level]);
		operators_left.push_back('+');
		solution = DFSN(input_numbers, level, operands_left, operators_left, target_value);
		if (!solution.empty()) {
			return solution;
		}

		operands_right = make_pair(operands_right.first, operands_right.second * input_numbers[level]);
		operators_right.push_back('*'); 
		solution = DFSN(input_numbers, level, operands_right, operators_right, target_value);
		if (!solution.empty()) {
			return solution;
		}

	}
	// signal that the DFS did not find a valid solution here
	vector<char> empty_vec;
	empty_vec.clear();
	return empty_vec;
}

// find solution for type L
vector<char> find_solution(vector<int> input_numbers, int target_value) {

	vector<char> operators;
	vector<char> operators_solution = DFS(input_numbers, 0, input_numbers[0], operators, target_value);

	// no solution
	if (operators_solution.empty()) {
		operators_solution.push_back('0');
	}

	return operators_solution;
}


vector<char> find_solutionN(vector<int> input_numbers, int target_value) {
	vector<char> operators;
	pair<int, int> operands(0, input_numbers[0]);

	vector<char> operators_solution = DFSN(input_numbers, 0, operands, operators, target_value);

	if (operators_solution.empty()) {
		operators_solution.push_back('0');
	}

	return operators_solution;
}


int main() {

	// parse input and create Scenarios

	string line;
	Scenario* s = NULL;
	int line_number = 0;

	stringstream ss;


	while (getline(cin, line)) {
		line_number++;
		ss.str(line);

		// input from first line
		if (line_number % 2 == 1) {
			s = new Scenario();
			int number;
			while (ss >> number) {
				s->numbers.push_back(number);
			}
		}
		else {
			// input from second line
			int target_value;
			char order_mode;
			ss >> target_value;
			ss >> order_mode;
			s->target_value = target_value;
			s->order_mode = order_mode;

			
			vector<int> input_numbers = s->numbers;

			// all processing and output

			if (s->order_mode == "L") {
				vector<char> solution_operators = find_solution(input_numbers, s->target_value);
				s->set_solution(solution_operators);
			}
			else if (s->order_mode == "N") {
				vector<char> solution_operators = find_solutionN(input_numbers, s->target_value);
				s->set_solution(solution_operators);
			}

			cout << s->output << endl;
				
		}
		ss.clear();
	}


	return 0;
}