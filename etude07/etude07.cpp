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

	Card() {
		value = -1;
		suit = -1;
	}
};

struct Hand {
	vector<Card*> cards;
	string output;
	string input;

	Hand(string input_) {
		input = input_;
		output = "";
	}
};

// comparator to sort a Hand
struct {
	bool operator()(Card* a, Card* b) const {
		return a->value + (a->suit * 0.25) < b->value + (b->suit * 0.25);
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
	vector<Hand*> hands;

	// 1: Read the line of input
	while (getline(cin, line)) {
		Hand* hand = new Hand(line);
		hands.push_back(hand);
	}

	cout << "exited the input loop" << endl;

	for (int i = 0; i < hands.size(); i++) {
		Hand* hand = hands[i];
		line = hand->input;
		vector<Card*> cards;
		Card* card;
		char separator_type;
		string output = "";
		string error_msg = "";
		bool processing_card = false;
		bool error_flag = false;

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
					if (!card) {
						// out of order
						cout << c;
						error_msg = "out of order";
						error_flag = true;
					}
					else {
						if (c >= 48 && c <= 51) { // digit 0-3
							if (c == 48) {
								card->value = 10;
							}
							else if (c == 49) {
								card->value = 11;
							}
							else if (c == 50) {
								card->value = 12;
							}
							else if (c == 51) {
								card->value = 13;
							}
						}
						else {
							error_msg = "Invalid";
							error_flag = true;
						}
					}
				}
				else {
					// first number in card
					card = new Card();
					card->value = c - 48;
				}
			}
			// c is a letter
			else if (c >= 65 && c <= 90 || c >= 97 && c <= 122) {
				// either A,J,Q,K, or suit 
				if (processing_card) {
					// suit
					// assign suit value to card
					try {
						if (c == 67 || c == 99) { // club
							card->suit = 0;
						}
						else if (c == 72 || c == 104) { // heart
							card->suit = 2;
						}
						else if (c == 83 || c == 115) { // spade
							card->suit = 3;
						}
						else if (c == 68 || c == 100) { // diamond
							card->suit = 1;
						}
						else {
							error_msg = "invalid suit";
							error_flag = true;
						}
					}
					catch (exception& e) {
						error_msg = "Hand empty when it shouldn't be, implies invalid input";
						error_flag = true;
					}
				}
				else {
					// A,J,Q, or K
					card = new Card();
					processing_card = true;
					if (c == 65 || c == 97) {
						card->value = 1; // Ace
					}
					else if (c == 74 || c == 106) {
						card->value = 11; // Jack
					}
					else if (c == 81 || c == 113) {
						card->value = 12; // Queen
					}
					else if (c == 75 || c == 107) {
						card->value = 13; // King
					}
					else {
						cout << "c";
						error_msg = "not A,J,Q, or K";
						error_flag = true;
					}
				}
			}
			else if (c == DASH_CHAR || c == SPACE_CHAR || c == FORWARD_SLASH_CHAR) {
				// determine if the separator type is valid or set the initial type
				if (cards.size() == 0) {
					separator_type = c;
				}
				else if (c != separator_type) {
					error_msg = "Inconsistent separator type";
					error_flag = true;
				}

				if (processing_card) {
					// end card
					cards.push_back(card);
					cout << "adding card: " << card->value << "," << card->suit << endl;
					card = new Card();
					processing_card = false;
				}
				else {
					// two spacers in a row, error
					error_msg = "two spacers in a row";
					error_flag = true;
				}

			}
			else {
				error_msg = "unrecognized input";
				error_flag = true;
			}

			if (error_flag) {
				hand->output = "Invalid: " + hand->input;
				break;
			}
		}

		if (error_flag) {
			cout << error_msg << endl;
		}


		// 2: Checks whether the input is a valid poker hand
		// if there are 5 cards and no errors, its a valid hand: sort it. otherwise, do nothing
		if (cards.size() == 5 && !error_flag) {
			// sort it
			sort(cards.begin(), cards.end(), cardSort);
			hand->cards = cards;
		}


	} // end for loop

	cout << "exited the processing loop" << endl;

	// 3: for each hand, If the input is valid, outputs the poker hand in std format, otherwise outputs "Invalid: [input]"
	for (int i = 0; i < hands.size(); i++) {
		Hand* hand = hands[i];
		cout << hand->output << endl;

		vector<Card*> cards = hand->cards;
		for (int j = 0; j < cards.size(); j++) {
			Card* card = cards[j];
			cout << card->value << "," << card->suit << endl;
		}
	}

}