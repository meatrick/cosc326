#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

#define NUM_CARDS 5
#define DASH_CHAR 45
#define SPACE_CHAR 32
#define FORWARD_SLASH_CHAR 47

struct Card {
	int value = -1; // 2-13, 1
	double suit = -1; // 0=clubs, 1=diamonds, 2=hearts, 3=spades
};

struct Hand {
	vector<Card> cards;
	string output = "";
};

// comparator to sort a Hand
struct {
	bool operator()(Card a, Card b) const {
		return a.value + (a.suit * 0.25) < b.value + (b.suit * 0.25);
	}
} cardSort;
//use sort(s.begin(), s.end(), cardSort)

// for each line,
	// read the line
	// create a Hand
	// determine the output
// for each Hand, print the output


int main() {
	string line = "";

	while (cin >> line) {
		// 1: Read the line of input
		Hand hand;
		vector<Card> cards;
		Card card;
		char separator_type;
		string output = "";
		bool processing_card = false;

		// need a flag: currently processing a new card t/f
		// if its a number and flag = f
		// else if its a number and flag = t
		// else if its a letter and flag = f
		// else if its a letter and flag = t
		// else if its a separator and flag = t, check if card is valid
			// if yes, set flag = f


		int len = line.size();
		for (int i = 0; i < len; i++) {
			char c = line[i];
			if (c >= 48 && c <= 57) { // digit 0-9
				if (processing_card) {
					// either out of order or second digit of 10-13
					
				}
				else {
					// first number in card
					card.value = c - 48;
				}
			}
			// c is a letter
			else if (c >= 65 && c <= 90 || c >= 97 && c <= 122) {
				// either A,J,Q,K, or suit 
				if (processing_card) {
					// suit
				}
				else {
					// A,J,Q, or K
				}



				// assign suit value to card
				try {
					Card card = cards.back();
					if (c == 67 || c == 99) { // club
						card.suit = 0;
					}
					else if (c == 72 || c == 104) { // heart
						card.suit = 2;
					}
					else if (c == 83 || c == 115) { // spade
						card.suit = 3;
					}
					else if (c == 68 || c == 99) { // diamond
						card.suit = 1;
					}
				} catch (exception& e) {
					output = "Hand empty when it shouldn't be, implies invalid input";
				}
			}
			else if (c == DASH_CHAR || c == SPACE_CHAR || c == FORWARD_SLASH_CHAR) {
				if (processing_card) {
					// end card
				}
				else {
					// two spacers in a row, error
				}

				if (cards.size() == 1) {
					separator_type = c;
				}
				else if (c != separator_type) {
					output = "Inconsistent separator type";
					
				}
			}
			else {
				output = "Invalid input";
			}
		}


		// 2: Checks whether the input is a valid poker hand
		// sort the hand if it is

		// 3: If the input is valid, outputs the poker hand in std format, otherwise outputs "Invalid: [input]"

	}
}