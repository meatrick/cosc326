#include <iostream>
#include <cstdlib>
#include <string>
#include <istream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

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

	// method: given a scenario object and a solution, create the output for the solution
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



string increment_bitstring(string bitstring) {
	size_t len = bitstring.size();
	char lsb = bitstring[len - 1];
	if (lsb == '0') {
		bitstring[len - 1] = '1';
	}
	else {
		bitstring = increment_bitstring(bitstring.substr(0, len - 1));
		bitstring += '0';
	}

	return bitstring;
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
		// iterate through all permutations of list of numbers
		vector<int> vec_numbers(sc->numbers);
		int len = vec_numbers.size();


		// create a binary string of length equal to the number of operands - 1
		string bitstring = "";
		for (int i = 0; i < len - 1; i++) {
			bitstring += "0";
		}
		// this binary string starts at zero
		// var solution = NULL;
		string solution = "-1";
		bool solution_found = false;

		// if LtoR order of operations, do:
		if (sc->order_mode == "L") {
			// from 0 to the max number that binary string can go, do:
			do {
				// add the first number to the sum
				int sum = vec_numbers[0];
				// for each bit of the bitstring, from left to right, do:
				for (int i = 0; i < len - 1; i++) {
					// if the bit reads 0, add the the i+1th number to the sum
					if (bitstring[i] == '0') {
						sum += vec_numbers[i + 1]; // never out of bounds

					}
					// if the bit reads 1, multiply the sum by the i+1th number
					else if (bitstring[i] == '1') {
						sum *= vec_numbers[i + 1];
					}
				}
				// if the sum is equal to the goal number, set a flag, save the bitstring, and break from the loop
				if (sum == sc->target_value) {
					solution_found = true;
					solution = bitstring;
					break;
				}
				else {
					// else, continue (increment bitstring)
					// terminate loop if this iteration was "11....1"
					size_t found = bitstring.find("0");
					if (found == string::npos) {
						break;
					}
					// otherwise, increment
					bitstring = increment_bitstring(bitstring);

				}

			} while (true);
		}

		// else if normal order of operations, do:
		else if (sc->order_mode == "N") {
			// save the original bitstring and make a copy of the bistring

			// len = size of bitstring + 1 (number of operands)

			bool repeat = false;
			// from 0 to the max number that the binary string can go, do:
			do {
				vector<int> vec_numbers_cpy(vec_numbers);
				int bitstring_len = bitstring.size();
				string bitstring_cpy = bitstring;
				int sum = 0;

				// for i = 0 to len - 1, do:
				for (int i = 0; i < bitstring_len; i++) {
					// if there are only +'s left:
					size_t find = bitstring_cpy.find("1");
					if (find == string::npos) {
						// all the multiplications are gone.  Do a pass and add everything together
						while (!vec_numbers_cpy.empty()) {
							sum += vec_numbers_cpy.back();
							vec_numbers_cpy.pop_back();
						}
						break;
					}
					// if the bit = 0:
					if (bitstring_cpy[i] == '0') {
						// continue to the next bit
						continue;
					}
					// else if the bit = 1:
					else if (bitstring_cpy[i] == '1') {
						vec_numbers_cpy[i] *= vec_numbers_cpy[i + 1];
						// erase bit i from the bitstring and erase vec[i+1] from the vector of numbers
						bitstring_cpy.erase(i, 1);
						int pos_to_erase = i + 1;
						vec_numbers_cpy.erase(vec_numbers_cpy.begin() + pos_to_erase);

						bool repeat = true;
						bitstring_len = bitstring_cpy.size();

						// if (repeat)
						if (repeat) {
							i = i - 2;
							repeat = false;
							continue;
						}
					}
				}
				// if sum == goal:
				if (sum == sc->target_value) {
					// save original bitstring, set a flag, break from the loop
					solution = bitstring;
					solution_found = true;
					break;
				}
				// else, continue to the next bitstring
				else {
					// terminate loop if this iteration was "11....1"
					size_t found = bitstring.find("0");
					if (found == string::npos) {
						break;
					}
					// otherwise, increment
					bitstring = increment_bitstring(bitstring);
				}

			} while (true);
		}


		sc->set_solution(solution);

	}


	// output
	for (Scenario* sc : scenarios) {
		cout << sc->output << endl;
	}






	return 0;
}