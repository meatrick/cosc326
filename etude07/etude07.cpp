#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

#define NUM_CARDS 5
#define DASH_CHAR 45
#define SPACE_CHAR 32
#define FORWARD_SLASH_CHAR 47
const string values_to_output[] = { "-1", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
const string suit_to_output[] = { "C", "D", "H", "S" };

struct Card {
	int value; // 2-13, 1
	int suit; // 0=clubs, 1=diamonds, 2=hearts, 3=spades

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
		int val_a = a->value;
		int val_b = b->value;
		if (val_a == 1) {
			val_a = 14;
		}
		if (val_b == 1) {
			val_b = 14;
		}

		return val_a + (a->suit * 0.25) < val_b + (b->suit * 0.25);
	}
} cardSort;
//use sort(s.begin(), s.end(), cardSort)


int main() {
	string line = "";
	vector<Hand*> hands;

	// 1: Read the line of input
	while (getline(cin, line)) {
		Hand* hand = new Hand(line);
		hands.push_back(hand);
	}

	for (int j = 0; j < hands.size(); j++) {
		Hand* hand = hands[j];
		line = hand->input;
		Card* card;
		char separator_type;
		string output = "";
		string error_msg = "";
		bool processing_card = false;
		bool error_flag = false;


		int len = line.size();

		if (line[0] == ' ' || line[len - 1] == ' ') {
			error_flag = true;
		}

		for (int i = 0; i < len; i++) {
			char c = line[i];

			// if this char is the last char of the line
			if (i == len - 1) {
				// it must be the suit
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
					error_flag = true;
				}

				// add the card to the hand
				hand->cards.push_back(card);
				card = NULL;
				processing_card = false;
			}

			else if (c >= 48 && c <= 57) { // digit 0-9
				if (processing_card) {
					// either out of order or second digit of 10-13
					if (processing_card && !card) {
						// out of order
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
							error_flag = true;
						}
					}
				}
				else {
					// first number in card
					card = new Card();
					processing_card = true;
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
							error_flag = true;
						}
					}
					catch (exception& e) {
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
						error_flag = true;
					}
				}
			}
			else if (c == DASH_CHAR || c == SPACE_CHAR || c == FORWARD_SLASH_CHAR) {
				// determine if the separator type is valid or set the initial type
				if (hand->cards.size() == 0) {
					separator_type = c;
				}
				else if (c != separator_type) {
					error_flag = true;
				}

				if (processing_card) {
					// end card
					hand->cards.push_back(card);
					card = NULL;
					processing_card = false;
				}
				else {
					// two spacers in a row, error
					error_flag = true;
				}

			}
			else {
				error_flag = true;
			}

			if (error_flag) {
				hand->output = "Invalid: " + hand->input;
				break;
			}
		}

		if (!error_flag) {
			Card* card1;
			Card* card2;
			for (int i = 0; i < hand->cards.size(); i++) {
				card1 = hand->cards[i];
				for (int k = i + 1; k < hand->cards.size(); k++) {
					card2 = hand->cards[k];
					if (card1->value == card2->value && card1->suit == card2->suit) {
						error_flag = true;
						break;
					}
				}
				if (error_flag) break;
			}
		}

		// check for invalid input: not a full hand
		if (hand->cards.size() != NUM_CARDS) {
			error_flag = true;
		}

		if (error_flag) {
			hand->output = "Invalid: " + hand->input;
		}



		// 2: Checks whether the input is a valid poker hand
		// if there are 5 cards and no errors, its a valid hand: sort it. otherwise, do nothing
		if (hand->cards.size() == NUM_CARDS && !error_flag) {
			// sort it
			sort(hand->cards.begin(), hand->cards.end(), cardSort);

			string output;
			for (int j = 0; j < hand->cards.size(); j++) {
				Card* card = hand->cards[j];

				// format output
				output += values_to_output[card->value] + suit_to_output[card->suit];

				// add spaces after all but the last card
				if (j != 4) {
					output += " ";
				}
			}
			hand->output = output;
		}


	} // end for loop

	// 3: for each hand, If the input is valid, outputs the poker hand in std format, otherwise outputs "Invalid: [input]"
	for (int i = 0; i < hands.size(); i++) {
		Hand* hand = hands[i];
		vector<Card*> cards = hand->cards;
		cout << hand->output << endl;

	}
}