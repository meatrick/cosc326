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
	int value; // 2-13, 1
	double suit; // 0=clubs, 1=diamonds, 2=hearts, 3=spades
};

struct Hand {
	vector<Card> cards;
};

// comparator to sort a Hand
struct {
	bool operator()(Card a, Card b) const {
		return a.value + (a.suit * 0.25) < b.value + (b.suit * 0.25);
	}
} cardSort;
//use sort(s.begin(), s.end(), cardSort)


int main() {
	string line = "";

	while (cin >> line) {
		// 1: Read the line of input
		Hand hand;
		vector<Card> cards;
		int separator_type;

		int len = line.size();
		for (int i = 0; i < len; i++) {
			char c = line[i];
			if (c >= 48 && c <= 57) { // digit 0-9
				// peek next char
				try {
					char c_next = line[i + 1];
					if (c_next >= 48 && c <= 57) {
						Card card;
						card.value = ((c - 48) * 10) + c_next - 48;
						cards.push_back(card);
					}
				}
				catch (exception& e) {
					cout << "OOB error when peeking to see if # is double digit implies Invalid input\n";
				}
			}
			// c is a letter
			else if (c >= 65 && c <= 90 || c >= 97 && c <= 122) {
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
					cout << "Hand empty when it shouldn't be, implies invalid input\n";
				}
			}
			else if (c == DASH_CHAR || c == SPACE_CHAR || c == FORWARD_SLASH_CHAR) {
				//separator_type = c;
			}
			else {
				cout << "Invalid input" << endl;
			}
		}


		// 2: Checks whether the input is a valid poker hand
		// 3: If the input is valid, outputs the poker hand in std format, otherwise outputs "Invalid: [input]"

	}
}