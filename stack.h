
#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include <vector>
#include <iostream>
#include "card.h"


class Stack{
	public:
	std::vector<card> drawn;
	int score;
	int acee = 0;
	

	
	virtual void draw(){
		card c = card();
		drawn.push_back(c);
			if (c.get_face() == card_face::ten || c.get_face() == card_face::jack || c.get_face() == card_face::queen || c.get_face() == card_face::king){
				score += 10;
			}
			if (c.get_face() == card_face::two){
				score += 2;
			}
			if (c.get_face() == card_face::three){
				score += 3;
			}
			if (c.get_face() == card_face::four){
				score += 4;
			}
			if (c.get_face() == card_face::five){
				score += 5;
			}
			if (c.get_face() == card_face::six){
				score += 6;
			}
			if (c.get_face() == card_face::seven){
				score += 7;
			}
			if (c.get_face() == card_face::eight){
				score += 8;
			}
			if (c.get_face() == card_face::nine){
				score += 9;
			}
			if (c.get_face() == card_face::ace){
				if (score+11 <= 21){
					score += 11;
				}else{
					score +=1;
				}
			}
			if (score >21 && acee == 0){
				for (int i = 0; i <drawn.size(); i++){
					if (drawn[i].get_face() == card_face::ace){
						score -=10;
						acee +=1;
						break;
					}
				}
			}
	}	
};

std::ostream& operator<<(std::ostream& o, const Stack& sb) {
	for (int i = 0; i <sb.drawn.size(); i++){
		o<<"["<< sb.drawn[i];
	}
	o<<"]";
	return o;
}
#endif