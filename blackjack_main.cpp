#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "stack.h"

#include <vector>



using namespace std;

//global
int bet = 0;			//ammount bet
int chips = 1000;		//starting chips

void print_table_hidden(Stack drawn_player, Stack drawn_dealer){ 			//print function for when second dealer card must be hidden 
	cout << "\x1B[2J\x1B[H";
	cout<<"\x1B[93mBalance : \033[0m[" << chips-bet << "]"<<endl;
	cout<<"\x1B[93mYour Bet : \033[0m[" << bet << "]"<<endl;
	cout<<endl;

	if (drawn_player.drawn.size() < 2){
		cout<<"\x1B[32m====================================\033[0m"<<endl;
		cout<<"["<<drawn_dealer.drawn[0] << "]"<<endl;
		cout<<""<<endl;
		cout<<drawn_player <<"   :   " <<drawn_player.score<< endl;
		cout<<"\x1B[32m======Press Enter to continue=======\033[0m"<<endl;
		cout<<endl;
	}else {																	//[XX] as hidden card 
		cout<<"\x1B[32m====================================\033[0m"<<endl;
		cout<<"["<<drawn_dealer.drawn[0] << "[XX]"<<endl;
		cout<<""<<endl;
		cout<<drawn_player <<"   :   " <<drawn_player.score<< endl;
		cout<<"\x1B[32m====================================\033[0m"<<endl;
		cout<<endl;
	}
}

void print_table_full(Stack drawn_player, Stack drawn_dealer){				//print function for full hands
	cout << "\x1B[2J\x1B[H";
	cout<<"\x1B[93mBalance : \033[0m[" << chips-bet << "]"<<endl;
	cout<<"\x1B[93mYour Bet : \033[0m[" << bet << "]"<<endl;
	cout<<endl;

	cout<<"\x1B[32m====================================\033[0m"<<endl;
	cout<<drawn_dealer << "   :   " <<drawn_dealer.score<< endl;
	cout<<""<<endl;
	cout<<drawn_player <<"   :   " <<drawn_player.score<< endl;
	cout<<"\x1B[32m====================================\033[0m"<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////
int black_jack1(){
	/*STARTING GAME 
		return 0 = loss (lose bet)
		return 1 = win (double bet)
		return 2 = push (keep bet)
		return 3 = blackjack (3:2 win)
	*/
	
	//INITIALIZING STACK CLASS 
	Stack drawn_player;
	Stack drawn_dealer;
	drawn_player.score = 0;
	drawn_dealer.score = 0;
	
	drawn_player.draw(); 							//calling draw card function in stack class
	drawn_dealer.draw();
	
	print_table_hidden(drawn_player, drawn_dealer); //calling print function 
	cin.ignore();cin.ignore();  					//prompt user to press enter 
	
	drawn_dealer.draw();
	drawn_player.draw();
	
	print_table_hidden(drawn_player, drawn_dealer); 

	if (drawn_player.score == 21) {					//if player gets 21 blackjack first hand 
		cout<<"\x1B[33mBlack Jack!\033[0m";
		cin.ignore();cin.ignore();
		
		print_table_full(drawn_player, drawn_dealer);
		
		if (drawn_dealer.score == 21){				//check dealer score, if 2, push is returned 
			cout << "\x1B[34mPush!\033[0m";
			return 2;	//push
		}
		cout<<endl;
		cout << "You Win!";
		return 3;		//blackjack win
	}
	if (drawn_dealer.score == 21) {					//if dealer gets 21 blackjack first hand 
		print_table_full(drawn_player, drawn_dealer);
		cout<<"\x1B[31mDealer Black Jack!\033[0m";
		return 0;		//loss
	}
	
	/*PLAYER TURN
		player can hit or stand
	*/
	
	char hit_stand;									//prompt user to hit or stand
	cout<<"\x1B[35mWould you like to hit or stand\033[0m \x1B[33m[h/s]\033[0m : ";
	cin>>hit_stand;
	cout<<endl;
	
	while (hit_stand != 's'){ 						//while user does not stand 
		drawn_player.draw();
		
		print_table_hidden(drawn_player, drawn_dealer);
		cin.ignore();
		
		if (drawn_player.score > 21){				//if player busts 
			
			print_table_full(drawn_player, drawn_dealer);
			cout<<"\x1B[31m---------------BUST!----------------\033[0m";
			cin.ignore();
			
			return 0;	//loss
		}else if (drawn_player.score == 21){		//if player gets black jack 
			cout<<"\x1B[33m------------Black Jack!-------------\033[0m";
			break;
		}
		
		cout<<"\x1B[35mWould you like to hit or stand\033[0m \x1B[33m[h/s]\033[0m : ";
		cin>>hit_stand;
		cout<<endl;
	}
	
	print_table_full(drawn_player, drawn_dealer);
	cin.ignore();cin.ignore();
	cout<<endl;
	
	//Compare values  IF DEALER SCORE IS EQUAL TO OR GREATER THAN 17 [dealer cannot draw]
	if (drawn_dealer.score > drawn_player.score && drawn_dealer.score <=21 && drawn_dealer.score >= 17){
		
		print_table_full(drawn_player, drawn_dealer);
		
		cout << "\x1B[31mDealer wins!\033[0m";
		return 0; 		//loss
	}
	if (drawn_dealer.score < drawn_player.score && drawn_dealer.score <=21 && drawn_dealer.score >= 17){
		
		print_table_full(drawn_player, drawn_dealer);
		
		cout << "\x1B[33mYou win!\033[0m" ;
		return 1;		//win
	}
	if (drawn_dealer.score < drawn_player.score && drawn_dealer.score <=21 && drawn_dealer.score >= 17){
		
		print_table_full(drawn_player, drawn_dealer);
		
		cout << "\x1B[34mPush!\033[0m";
		return 2;		//push
	}
	
	/*DEALER TURN
		dealer draws cards untill over 17
	*/
	
	while (drawn_dealer.score < 17){
		drawn_dealer.draw();
		
		print_table_full(drawn_player, drawn_dealer);
		
		if (drawn_dealer.score > drawn_player.score && drawn_dealer.score <=21 && drawn_dealer.score >= 17){
			cout << "\x1B[31mDealer wins!\033[0m";
			return 0;	//loss
		}else if (drawn_dealer.score < drawn_player.score && drawn_dealer.score <=21 && drawn_dealer.score >= 17){
			cout << "\x1B[33mYou win!\033[0m" ;
			return 1;	//win
		}else if(drawn_dealer.score == drawn_player.score && drawn_dealer.score <=21 && drawn_dealer.score >= 17){
			cout << "\x1B[34mPush!\033[0m";
			return 2;	//push
		}else if (drawn_dealer.score >21){
			cout << "\x1B[33mDealer bust!\033[0m";
			if (drawn_player.score <=21){
				cout<<" You win";
			}
			return 1;	//winn
		}
		//cin.ignore();
		cout<<endl;
	}
	return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////


int main() {
	cout << "\x1B[2J\x1B[H"; //clear (kindof)
	cout<<"--------------------------------------------------------\033[0m"<<endl;
	cout<<"|         Welcome to the Console Blackjack!            \033[0m|"<<endl;
	cout<<"--------------------------------------------------------\033[0m"<<endl;
	srand(time(NULL));
	char prompt; 
	cout<<"\x1B[35mYou have been credited with 1000 chips.\033[0m" <<endl; //Starting with 1000 chips 
	cout<<endl;
	
	cout<<"\x1B[93mBalance : \033[0m[" << chips << "]"<<endl;			//printing balance for player 
	cout<<endl;
	
	cout<<"\x1B[35mReady to play?\033[0m \x1B[33m[y/q]\033[0m : ";
	cin>>prompt;
	cout<<endl;
	while (prompt != 'q'){												//while q (quit) is not entered 
		cout << "\x1B[2J\x1B[H";
		cout<<"\x1B[93mBalance : \033[0m[" << chips << "]"<<endl;
		cout<<endl;
		
	
		cout<<"\x1B[35mPlace your bets\033[0m : ";
			cin>> bet;
		while (!std::cin.good()){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    		cout<<"\x1B[35mInput must be a number!\033[0m"<<endl;
			cout<<endl;
			cout<<"\x1B[35mPlace your bets\033[0m : ";
			cin>> bet;
		}
		while (bet > chips){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout<<"\x1B[35mNot enough currency!\033[0m"<<endl;
			cout<<endl;
			cout<<"\x1B[35mPlace your bets\033[0m : ";
			cin>> bet;
		}

		
		int win = black_jack1(); 										//calling game function
		cin.ignore();
		cout<<endl;
		cout<<endl;
		
		if (win == 0){													//if dealer wins 
			cout<<endl;
			chips = chips - bet;
			cout<<"\x1B[93mBalance : \033[0m[" << chips << "]"<<endl;
			cout<<endl;
		}else if (win == 1){											//if player wins 
			cout<<endl;
			chips += bet;
			cout<<"\x1B[93mBalance : \033[0m[" << chips << "]"<<endl;
			cout<<endl;
		}else if (win == 2){											//if player score matches dealers (push)
			cout<<endl;
			cout<<"\x1B[93mBalance : \033[0m[" << chips << "]"<<endl;
			cout<<endl;
		}else if (win == 3){											//if player gets 21 (black jack)
			cout<<endl;
			
			int x3to2 = bet / 2;										//player wins 3 chips for every 2 bet
			chips += (x3to2 *3);
			
			cout<<"\x1B[93mBalance : \033[0m[" << chips << "]"<<endl;
			cout<<endl;
		}

		cout << "\x1B[2J\x1B[H";
		cout<<"\x1B[93mBalance : \033[0m[" << chips << "]"<<endl;
		cout<<endl;
		
		cout<<"\x1B[35mWould you like to play again?\033[0m \x1B[33m[y/q]\033[0m :"; 
		cin>>prompt;
		cout<<endl;
	}
}
