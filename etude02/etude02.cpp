#include <iostream>
#include <vector>
#include <string>

// trim function from stack overflow
string trim(string& str) {
	size_t first = str.find_first_not_of(' ');
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

struct City { // Node
	string name;
};

struct Link { // Edge
	City* from;
	City* to;
	double fare;
};

int main() {
	vector<City*> map;

	// get and store input

	string line;

	// the first line is different than the rest
	getline(cin, line);
	line = trim(line);
	// parse line to get the two cities.  force them lowercase.

	while (getline(cin, line)) {
		line = trim(line);

		// parse input to get the two cities and the fair
		// if a city does not already exist in the map, create a city object and add it to map
		// create a link between the two cities

	}


	// do computation 
	vector<City*> route; // the optimal route




	// output
	string output = "";
	for (City* city : route) {
		output += city->name + "-";
	}
	output = output.substr(0, output.size() - 1); // remove the last dash
	cout << output;

}