#ifndef CARD_H
#define CARD_H
#include <iostream>

using namespace std;


enum class card_face {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};
enum class card_suit {heart, diamond, spade, club};
	
class card{
		card_face face;
		card_suit suit;

	public: 
		card() : face(card_face(rand() % 13)), suit(card_suit(rand() % 4)) {} 
			//parameterized constructor 
		card(card_face f, card_suit s) : face(f), suit(s) {}
			
			// get functions
		card_face get_face() const {
			return face;
		}
		card_suit get_suit() const {
			return suit;
		}
			
			
		bool operator ==(const card& sb) {
			if ((get_face() == sb.get_face() ) && (get_suit() == sb.get_suit())) { 
				return true;
			}else{
				return false;
			}
		}
};

std::ostream& operator<<(std::ostream& o, const card& sb) {
	switch(sb.get_face()) { 
		case card_face::ace:
			o<< "A";
			break;
		case card_face::two:
			o<< "2";
			break;
		case card_face::three:
			o<< "3";
			break;
		case card_face::four:
			o<< "4";
			break;
		case card_face::five:
			o<< "5";
			break;
		case card_face::six:
			o<< "6";
			break;
		case card_face::seven:
			o<< "7";
			break;
		case card_face::eight:
			o<< "8";
			break;
		case card_face::nine:
			o<< "9";
			break;
		case card_face::ten:
			o<< "10";
			break;
		case card_face::jack:
			o<< "J";
			break;
		case card_face::queen:
			o<< "Q";
			break;
		case card_face::king:
			o<< "K";
			break;
	}
	switch(sb.get_suit()) {
		case card_suit::heart:
			o<< "\x1B[31m♥\033[0m";
			break;
		case card_suit::diamond:
			o<< "\x1B[31m♦\033[0m";
			break;
		case card_suit::spade:
			o<< "\x1B[34m♠\033[0m";
			break;
		case card_suit::club:
			o<< "\x1B[34m♣\033[0m";
			break;
	}
	return o;
	
}

#endif
