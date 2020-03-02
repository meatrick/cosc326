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

int main () { 

    // parse input and create Scenarios
    cout << "Give input, enter 'Done' when finished:" << endl;

    vector<Scenario> scenarios;
    string line;
    Scenario s;
    int line_number = 0;
    char termination_key[] = "Done";
    bool terminate = false;

    while (!terminate && getline(cin, line)) {
        line_number++;
        stringstream ss(line);

        if (strcmp(line.c_str(), termination_key) == 0) {
            terminate = true;
        }

        // input from first line
        if (line_number % 2 == 1) {
            int number;
            s.numbers.clear();
            while (ss >> number) {
                s.numbers.push_back(number);
            }
        }
        else {
            // input from second line
            int target_value;
            char order_mode;
            ss >> target_value;
            ss >> order_mode;
            s.target_value = target_value;
            s.order_mode = order_mode;
        }

        if (!terminate && line_number % 2 == 0) {
            scenarios.push_back(s);
        }
    } 


    // do computation
    for (Scenario sc: scenarios) {
        // iterate through all permutations of list of numbers
        vector<int> vec_numbers = sc.numbers;
        int len = vec_numbers.size();
        int numbers[len];
        copy(vec_numbers.begin(), vec_numbers.end(), numbers);

        sort(numbers, numbers + len);

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