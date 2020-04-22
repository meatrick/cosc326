#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

#define NUM_VALID_DOMAIN_NAMES 6

using namespace std;

enum charType { upper_letter, lower_letter, at, underscore, dot, hyphen, number, unrecognized };
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
		Email* email = new Email(line_in);
		emails.push_back(email);
	}

	cout << endl; // for spacing

	// process input
	for (Email* email : emails) {

		try {
			string line = email->input;

			// convert all _at_ and _dot_
			while (true) {
				bool found_at = false, found_dot = false;

				size_t found = line.find("_at_");
				if (found != string::npos) {
					line.replace(found, 4, "@");
					found_at = true;
				}

				found = line.find("_dot_");
				if (found != string::npos) {
					line.replace(found, 5, ".");
					found_dot = true;
				}

				if (!found_at && !found_dot)
				{
					break;
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


			// check that there are valid domain and mailbox names
			size_t at_pos = line.find("@");
			charType type1 = getCharType(line[at_pos + 1]);

			if (!isValidDomainType(type1)) {
				throw "Invalid domain name";
			}

			charType type2 = getCharType(line[0]);
			if (!isValidDomainType(type2)) {
				throw "Invalid mailbox name";
			}



			// TODO: check for valid domain extension
			bool valid_ext = false;
			for (int i = 0; i < NUM_VALID_DOMAIN_NAMES; i++) {
				string domain_ext = domain_names[i];
				size_t ext_size = domain_ext.size();
				size_t extension_pos = line.find(domain_ext);
				size_t last_pos = line.size() - 1;
				if (extension_pos != string::npos) {
					valid_ext = true;
					if (extension_pos + ext_size != last_pos + 1) {
						valid_ext = false; // not in the last position
					}
					else break;
				}
			}
			if (!valid_ext) {
				throw "no valid domain extension";
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
