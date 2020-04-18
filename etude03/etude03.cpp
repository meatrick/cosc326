#include <iostream>
#include <cstdlib>
#include <string>
#include <istream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

struct Scenario {
	vector<int> numbers;
	int target_value;
	char order_mode;
	string output;
};

// method: given a scenario object and a solution, create the output for the solution
// if the solution is NULL, do the "impossible" output
// else ...

int main() {

	// parse input and create Scenarios

	vector<Scenario*> scenarios;
	string line;
	Scenario* s;
	int line_number = 0;


	while (getline(cin, line)) {
		line_number++;
		stringstream ss(line);

		// input from first line
		if (line_number % 2 == 1) {
			int number;
			s.numbers.clear();
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
	}


	// do computation for each scenario
	for (Scenario* sc : scenarios) {
		// iterate through all permutations of list of numbers
		vector<int> vec_numbers = sc->numbers;
		int len = vec_numbers.size();
		// int numbers[len];
		// copy(vec_numbers.begin(), vec_numbers.end(), numbers);
		// sort(numbers, numbers + len);

		// create a binary string of length equal to the number of operands - 1
		// this binary string starts at zero
		// var solution = NULL;

		// if LtoR order of operations, do:
		// from 0 to the max number that binary string can go, do:
			// sum = 0
			// add the first number to the sum
			// for each bit of the bitstring, from left to right, do:
				// if the bit reads 0, add the the i+1th number to the sum
				// if the bit reads 1, multiply the sum by the i+1th number
			// if the sum is equal to the goal number, set a flag, save the bitstring, and break from the loop
			// else, continue
		// pass the scenario and the solution to the method that will save the desired output to the scenario

		// else if normal order of operations, do:
		// save the original bitstring and make a copy of the bistring
		// len = size of bitstring
		// int sum = 0
		// from 0 to the max number that the binary string can go, do:
			// product = 0
			// for i = 0 to len, do:
				// if (repeat)
					// i--
					// repeat = false
				// if (i == len-1) 
					// all the multiplications are gone.  Do a pass and add everything together
					// size = vec.size()
					// for i to size-1, do:
						// sum += i
						// break
				// if the bit = 0:
					// continue to the next bit
				// else if the bit = 1:
					// vec[i] = vec[i] * vec[i+1]
					// erase bit i from the bitstring and erase vec[i+1] from the vector of numbers
					// bool repeat = true
					// len--
			// if sum == goal:
				// save original bitstring, set a flag, break from the loop
			// else, continue to the next bitstring
			// pass the scenario and solution to the method that will save the desired output to the scenario
				// if the bitstring is null or -1, that means it is impossible





		do {
			for (int i = 0; i < len; i++) {
				// a different permutations occurs here with each iteration
				if (sc.order_mode == 'N') { // normal OOO

				}
				else { // L to R OOO

				}
			}
		} while (next_permutation(numbers, numbers + len));

	}


	// output
	for (Scenario sc : scenarios) {
		cout << sc.output << endl;
	}


	/*  TESTING FOR SCENARIO OBJECT AND INPUT READING
	while (!scenarios.empty()) {
		reverse(scenarios.begin(), scenarios.end());
		Scenario s = scenarios.back();
		scenarios.pop_back();

		vector<int> numbers = s.numbers;
		for (int i = 0; i < numbers.size(); i++) {
			cout << numbers[i] << " ";
		}
		cout << endl;
		cout << "target: " << s.target_value << endl;
		cout << "mode: " << s.order_mode << endl;

	}
	*/



	return 0;
}