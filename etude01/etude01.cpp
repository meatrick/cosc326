#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include<sstream>

#define NUM_VALID_DOMAIN_NAMES 6

using namespace std;

enum charType { upper_letter, lower_letter, at, underscore, dot, hyphen, number, unrecognized, bracket };
const string domain_names[] = { "co.nz" , "com.au", "co.ca", "com", "co.us", "co.uk" };

struct Email {
	string input = "";
	string output = "";

	Email(string input_) {
		input = input_;
	}
};

// enum state {empty, on_name, read_underscore, }


charType getCharType(char c) {
	charType type;

	// determine type of character
	if (c >= 65 && c <= 90) {
		type = upper_letter;
	}
	else if (c >= 97 && c <= 122) {
		type = lower_letter;
	}
	else if (c == 64) {
		type = at;
	}
	else if (c == 95) {
		type = underscore;
	}
	else if (c == 46) {
		type = dot;
	}
	else if (c == 45) {
		type = hyphen;
	}
	else if (c >= 48 && c <= 57) {
		type = number;
	}
	else if (c == 91 || c == 93) {
		type = bracket;
	}
	else {
		type = unrecognized;
	}

	return type;
}

bool isValidDomainType(charType type) {
	if (type == lower_letter || type == upper_letter
		|| type == hyphen || type == underscore
		|| type == number) {
		return true;
	}

	return false;
}

int main() {
	string line_in;
	vector<Email*> emails;

	// get input
	while (getline(cin, line_in)) {

		if (line_in.empty()) continue; // skip if the line is empty

		Email* email = new Email(line_in);
		emails.push_back(email);
	}

	cout << endl; // for spacing

	// process input
	for (Email* email : emails) {

		try {
			string line = email->input;
			bool uses_sq_brackets = false;

			// convert _at_ to @
			size_t found_at_symbol = line.find("@");
			size_t found = line.rfind("_at_");

			if (found_at_symbol != string::npos) {
				// do nothing
			}
			else if (found != string::npos) {
				line.replace(found, 4, "@");
			}


			// replace "_dot"
			while (true) {
				bool found_dot = false;
				size_t found = line.find("_dot_");
				if (found != string::npos) {
					line.replace(found, 5, ".");
					found_dot = true;
				}
				if (!found_dot) break;
			}


			// check for double separators
			for (size_t i = 1; i < line.size(); i++) {
				char c_curr = line[i];
				charType type_curr = getCharType(c_curr);
				char c_last = line[i-1];
				charType type_last = getCharType(c_last);

				if ((type_last == underscore || type_last == dot || type_last == hyphen)
				&& (type_curr == underscore || type_curr == dot || type_last == hyphen)) {
					throw "double separator";
				}
				
			}

			// check string for correct number of @'s
			size_t num_ats = 0;
			string line_copy = line;
			while (true) {
				size_t found = line_copy.find("@");
				if (found != string::npos) {
					num_ats++;
					line_copy.erase(found, 1);
				}
				else break;
			}
			if (num_ats > 1) {
				throw "too many '@'s";
			}
			else if (num_ats < 1) {
				throw "missing @";
			}

			// check for valid mailbox name
			charType type2 = getCharType(line[0]);
			if (!isValidDomainType(type2)) {
				throw "Invalid mailbox name";
			}

			// find @ pos, used for checking position of [...] and domain name
			size_t at_symbol_pos = line.find("@");
			charType char_type_after_at_symbol = getCharType(line[at_symbol_pos + 1]);


			// look for [...] domain name & extension
			size_t num_left_brackets = 0, num_right_brackets = 0;
			// count num of brackets
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == 91) {
					num_left_brackets++;
				}
				else if (line[i] == 93) {
					num_right_brackets++;
				}
			}
			if (num_left_brackets != num_right_brackets) {
				throw "brackets do not match";
			}
			if (num_left_brackets > 1 || num_right_brackets > 1) {
				throw "too many brackets";
			}
			if (num_left_brackets == 1 && num_right_brackets == 1) { // valid brackets
				uses_sq_brackets = true;

				int left_bracket_pos = line.find("[");
				int right_bracket_pos = line.find("]");

				// discount if the right bracket is not at the end of the line
				if (right_bracket_pos != line.size() - 1) {
					throw "right square bracket not at end of line";
				}

				// check the contents inside the brackets
				int num_dots = 0;
				int num_of_digits_since_last_dot = 0;
				vector<int> dot_positions;
				dot_positions.clear();
				// stoi()

				for (int i = left_bracket_pos + 1; i < right_bracket_pos; i++) {
					charType type = getCharType(line[i]);
					if (type != dot && type != number) {
						throw "contents of domain bracket invalid";
					}

					if (num_of_digits_since_last_dot == 0 && type == dot) {
						throw "invalid domain format: consecutive dots";
					}

					if (type == dot) {
						num_of_digits_since_last_dot = 0;
						dot_positions.push_back(i);
						num_dots++;
						if (num_dots > 3) {
							throw "invalid domain format: too many dots";
						}
					}
					else {
						num_of_digits_since_last_dot++;
					}


				}
				if (num_dots != 3 || num_of_digits_since_last_dot == 0) {
					throw "invalid domain syntax";
				}

				// first bit
				string num = "";
				vector<int> ip_nums;
				ip_nums.clear();
				for (int i = left_bracket_pos + 1; i < dot_positions[0]; i++) {
					num += line[i];
				}
				ip_nums.push_back(stoi(num));
				num = "";

				// 2nd and 3rd bit
				for (int j = 0; j < 2; j++) {
					for (int i = dot_positions[j] + 1; i < dot_positions[j + 1]; i++) {
						num += line[i];
					}
					ip_nums.push_back(stoi(num));
					num = "";
				}
				// 4th bit
				for (int i = dot_positions[2] + 1; i < right_bracket_pos; i++) {
					num += line[i];
				}
				ip_nums.push_back(stoi(num));


				for (int i = 0; i < ip_nums.size(); i++) {
					if (ip_nums[i] > 255) {
						throw "invalid bit in IP address";
					}
				}

			}


			if (!uses_sq_brackets) {

				// check that there is a valid domain name
				if (!isValidDomainType(char_type_after_at_symbol)) {
					throw "Invalid domain name";
				}


				// for each potential domain extension, search for it
				bool valid_ext = false;
				for (int i = 0; i < NUM_VALID_DOMAIN_NAMES; i++) {
					string domain_ext = domain_names[i];
					size_t ext_size = domain_ext.size();
					size_t extension_pos = line.find(domain_ext);
					size_t last_pos = line.size() - 1;
					if (extension_pos != string::npos) {
						valid_ext = true;
						if (extension_pos + ext_size != last_pos + 1) {
							throw "domain extension not at end of input";
						}
						else break;
					}
				}

				if (!valid_ext) {
					throw "no valid domain extension";
				}
			}


			// iterate over each character of the input line
			for (int i = 0; i < line.size(); i++) {
				char c = line[i];
				charType type = getCharType(c);

				if (type == unrecognized) {
					throw "unrecognized character(s)";
				}

				// convert uppercase to lowercase
				if (type == upper_letter) {
					line[i] += 32;
				}
			}


			// if no error has been thrown, set the output
			email->output = line;

		}
		catch (char const* error_msg) {
			email->output = email->input + " <-- " + error_msg;
		}

	}

	// output
	for (Email* email : emails) {
		cout << email->output << endl;
	}

	return 0;
}
