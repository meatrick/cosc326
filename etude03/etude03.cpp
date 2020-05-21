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

class Node {
public:
	int index;
	int init_value;
	int product;
	bool visited = false;

	Node(int index_, int init_value_) {
		index = index_;
		init_value = init_value_;
		product = init_value_;
	}

};


class NodeN {
public:
	int index;
	bool visited = false;
	int init_value;
	int product;
	vector<int> operands;

	NodeN(int index_, int init_value_) {
		index = index_;
		init_value = init_value_;
		product = init_value;
	}

};


vector<char> DFS(vector<int> input_numbers, size_t level, int partial_sum, vector<char> operators, int target_value) {
	// base case: if start_node is a leaf
	if (level == input_numbers.size() - 1) {
		if (partial_sum == target_value) {
			return operators;
		}
	}
	else {
		level++;
		vector<char> solution;

		// left child
		int left_partial_sum = partial_sum + input_numbers[level]; 
		operators.push_back('+');
		vector<char> solution = DFS(input_numbers, level, left_partial_sum, operators, target_value);
		if (!solution.empty()) {
			return solution;
		}
	
		int right_partial_sum = partial_sum * input_numbers[level];
		operators.push_back('*');
		vector<char> solution = DFS(input_numbers, level, right_partial_sum, operators, target_value);
		if (!solution.empty()) {
			return solution;
		}

	}
	// signal that the DFS did not find a valid solution here
	vector<char> empty_vec;
	empty_vec.clear();
	return empty_vec;
}

NodeN* DFSN(vector<NodeN*> tree, NodeN* start_node, int target_value) {
	start_node->visited = true;

	// base case: if start_node is a leaf
	if (start_node->index >= tree.size() / 2) {
		int sum = 0;
		for (int i = 0; i < start_node->operands.size(); i++) {
			sum += start_node->operands[i];
		}

		if (sum == target_value) {
			return start_node;
		}
	}
	else {
		int l_child_index = start_node->index * 2 + 1;
		int r_child_index = start_node->index * 2 + 2;
		NodeN* l_child = tree[l_child_index];
		NodeN* r_child = tree[r_child_index];



		if (!l_child->visited) {
			l_child->operands = start_node->operands;
			l_child->operands.push_back(l_child->init_value);
			NodeN* solution = DFSN(tree, l_child, target_value);
			if (solution) {
				return solution;
			}
		}
		if (!r_child->visited) {
			r_child->operands = start_node->operands;
			r_child->operands.back() *= r_child->init_value;
			NodeN* solution = DFSN(tree, r_child, target_value);
			if (solution) {
				return solution;
			}
		}
	}
	return NULL;
}

// find solution for type L
vector<char> find_solution(vector<int> input_numbers, int target_value) {

	vector<char> operators;
	vector<char> solution = DFS(input_numbers, 0, input_numbers[0], operators, target_value);

	// no solution
	if (operators.empty()) {
		operators.push_back('0');
	}

	return operators;
}


vector<char> find_solutionN(vector<NodeN*> tree, int target_value) {
	NodeN* root = tree[0];
	root->operands.push_back(root->init_value); // initialize operands vector

	NodeN* node = DFSN(tree, root, target_value);

	vector<char> operators;

	if (!node) {
		operators.push_back('0');
		return operators;
	}


	vector<NodeN*> path;
	path.push_back(node);

	// get parent
	while (true) {
		NodeN* parent;
		if (node->index == 0) {
			parent = NULL;
		}
		else if (node->index % 2 == 1) {
			parent = tree[node->index / 2];
		}
		else if (node->index % 2 == 0) {
			parent = tree[node->index / 2 - 1];
		}
		if (parent) {
			node = parent;
			path.push_back(node);
		}
		else {
			break;
		}
	}

	reverse(path.begin(), path.end());

	for (int i = 0; i < path.size(); i++) {
		NodeN* parent = path[i];
		if (parent->index < tree.size() / 2) {
			NodeN* child = path[i + 1];
			if (child->index == parent->index * 2 + 1) {
				operators.push_back('+');
			}
			else if (child->index == parent->index * 2 + 2) {
				operators.push_back('*');
			}
		}
	}
	return operators;
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
				vector<NodeN*> tree;
				int index = 0;
				for (size_t i = 0; i < input_numbers.size(); i++) {
					for (size_t j = 0; j < pow(2, i); j++) {
						tree.push_back(new NodeN(index, input_numbers[i]));
						index++;
					}
				}

				vector<char> solution_operators = find_solutionN(tree, s->target_value);
				s->set_solution(solution_operators);
			}

			cout << s->output << endl;
				
		}
		ss.clear();
	}


	return 0;
}