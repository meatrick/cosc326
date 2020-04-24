#include <iostream>
#include <cstdlib>
#include <string>
#include <istream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm> // for reversing vectors

using namespace std;

string increment_bitsting(string bitstring);

struct Scenario {
	vector<int> numbers;
	int target_value;
	string order_mode;
	string output;

	Scenario() {
		// init
	}

	// method: given a scenario object and a solution in the form of a bitstring, create the output for the solution
	// if the solution is -1, do the "impossible" output
	// else ...
	void set_solution(string solution) {
		if (solution == "-1") { // impossible
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
				string str_operator;
				if (solution[i] == '0') {
					str_operator = "+";
				}
				else {
					str_operator = "*";
				}
				this->output += str_operator + " ";
			}
		}

	}
};

class Node {
public:
	Node* parent = NULL;
	Node* left_child = NULL; // plus
	Node* right_child = NULL; // multiplication
	int init_value;
	int id;
	bool visited = false;
	int product;

	Node(int id_, int init_value_) {
		id = id_;
		init_value = init_value_;
		product = init_value;
	}

	void attach_left_child(Node* child) {
		left_child = child;
	}

	void attach_right_child(Node* child) {
		right_child = child;
	}

	bool is_leaf() {
		return !(left_child && right_child);
	}
};

class NodeL : public Node {
public:
	int product;

	// NodeL(int init_value) : Node(init_value) {
	//     product = init_value;
	// } 

};

class NodeN : public Node {
public:
	vector<int> operands;
};



class Edge {
public:
	Node* parent;
	Node* child;
	int operator_type;

	Edge(Node* parent_, Node* child_, int operator_type_) {
		parent = parent_;
		child = child_;
		operator_type = operator_type_;

		if (operator_type == 0) {
			parent->attach_left_child(child);
		}
		else if (operator_type == 1) {
			parent->attach_right_child(child);
		}
	}
};

class EdgeL : public Edge {
public:
};

class EdgeN : public Edge {
public:
	int operand;
};

class Tree {
public:
	vector<Node*> nodes;
	vector<Edge*> edges;
	Node* root;

	void set_root(Node* root_) {
		root = root_;
	}

	void create_edge(Node* parent, Node* child, int operator_type) {
		cout << operator_type << endl;
		Edge* edge = new Edge(parent, child, operator_type);
		edges.push_back(edge);
	}

	Tree(vector<int> input_numbers) {
		vector<int> tree_list;
		for (int i = 0; i < input_numbers.size(); i++) {
			for (int j = 0; j < pow(2, i); j++) {
				tree_list.push_back(input_numbers[i]);
			}
		}

		for (int i = 0; i < tree_list.size(); i++) {
			Node* node = new Node(i, tree_list[i]);
			if (i == 0) {
				set_root(node);
			}
			nodes.push_back(node);
		}

		for (int i = 0; i < nodes.size() / 2; i++) {
			int index_of_left_child = i * 2 + 1;
			int index_of_right_child = index_of_left_child + 1;

			create_edge(nodes[i], nodes[index_of_left_child], 0);
			create_edge(nodes[i], nodes[index_of_right_child], 1);
		}
	}

	string to_string() {
		string str = "";

		for (Edge* edge : edges) {
			str += "{" + std::to_string(edge->parent->init_value) + ", " + std::to_string(edge->child->init_value) + ", " + std::to_string(edge->operator_type) + "}\n";
		}
		return str;
	}

};

class TreeL : public Tree {
};

class TreeN : public Tree {
};

Node* DFS(Tree* t, Node* start_node, int target_value) {
	start_node->visited = true;

	// base case
	if (start_node->is_leaf()) {
		if (start_node->product == target_value) {
			return start_node;
		}
	}
	else {
		Node* l_child = start_node->left_child;
		Node* r_child = start_node->right_child;

		if (!l_child->visited) {
			l_child->product += start_node->product;
			Node* solution = DFS(t, l_child, target_value);
			if (solution) {
				return solution;
			}
		}
		if (!r_child->visited) {
			r_child->product *= start_node->product;
			Node* solution = DFS(t, r_child, target_value);
			if (solution) {
				return solution;
			}
		}
	}
	return NULL;
}

// find solution for type L
string find_solution(Tree* t, int target_value) {
	Node* node = DFS(t, t->root, target_value);

	string bitstring = "";

	vector<Node*> path;
	path.push_back(node);
	while (node->parent) {
		node = node->parent;
		path.push_back(node);
	}

	reverse(path.begin(), path.end());

	for (int i = 0; i < path.size(); i++) {
		if ()
	}


}


int main() {

	// parse input and create Scenarios

	vector<Scenario*> scenarios;
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

			// add the scenario to the list
			scenarios.push_back(s);
		}
		ss.clear();
	}



	// do computation for each scenario
	for (Scenario* sc : scenarios) {
		vector<int> input_numbers = sc->numbers;

		if (sc->order_mode == "L") {
			Tree* t = new Tree(sc->numbers); // create tree




		}
		else if (sc->order_mode == "N") {

		}





	}


	// output
	for (Scenario* sc : scenarios) {
		cout << sc->output << endl;
	}






	return 0;
}