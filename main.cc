#include <iostream>
#include <sstream>
#include <string>
#include "window.h"
#include "board.h"
#include "player.h"
#include "score.h"
using namespace std;

//white piece: K, Q, B, R, N, P
//blace piece: k, q, b, r, n, p
char pieces[12] = { 'K', 'Q', 'B', 'R', 'N', 'P', 'k', 'q', 'b', 'r', 'n', 'p' };

bool validPosition(int x, int y) { //return true if x, y is a valid position in board, false otherwise
	if(0 <= x && x <= 7 && 0 <= y && y <= 7) return true;
	return false;
}

bool validPiece(char c){
	for (int i = 0; i < 12; ++i){
		if (c == pieces[i]){
			return true;
		}
	}
	return false;
}
bool validPlayer(string s1, string s2){
	if (s1 == "human" || s1 == "computer[1]" || s1 == "computer[2]" || s1 == "computer[3]" || s1 == "computer[4]"){
		if (s2 == "human" || s2 == "computer[1]" || s2 == "computer[2]" || s2 == "computer[3]" || s2 == "computer[4]"){
			return true;
		}
	}
	return false;
}

int main() {
	cout << "Welcome to chess game!" << endl;
	 
	cin.exceptions(ios::eofbit|ios::failbit);
	string cmd;
	Score score;
	Board board;
	Player whitePlayer{ true, &board };
	Player blackPlayer{ false, &board };
	whitePlayer.set_player(&blackPlayer);
	blackPlayer.set_player(&whitePlayer);
	bool whiteTurn = 1;
	bool isSetup = 0;
	bool gameStart = 0;

    try {
	while (true) {
		if(!gameStart && !isSetup) cout << "You can set up your own initial board configurations or start a new game. " << endl;
		cin >> cmd;
		if (cin.eof()) break;
		if (cmd == "setup") {
			whitePlayer.clearPlayer();
			blackPlayer.clearPlayer();
            board.initsetup();
			while (true) {
				if (gameStart) {
					cout << "Cannot setup when game is currently running!" << endl;
					break;
				}
				cin >> cmd;
				int x;
				int y;

				if (cmd == "done") {
					if (!whitePlayer.setup()) {
						cout << "Please set up white pieces again." << endl;
						continue;
					}
					if (!blackPlayer.setup()) {
						cout << "Please set up black pieces again." << endl;
						continue;
					}
					
						isSetup = 1;
						cout << "Set up is done! Please start a new game." << endl;
						break; //finish set up
					
				}else if (cmd == "+") { // add piece to the position
					char piece;
					string position;
					
						cin >> piece;
						cin >> position;
						x = position[0] - 'a';
						y = position[1] - '1';
						if (validPosition(x, y) && validPiece(piece)) {
							if ('A' <= piece && piece <= 'Z'){
								whitePlayer.add_chess(piece, x, y);
							}
							else{
								blackPlayer.add_chess(piece, x, y);
							}
							cout << board;
							
						}
						else {
							cout << "Invalid piece or position. Please re-enter." << endl;
                            continue;
						}
					
				}else if (cmd == "-") { // remove piece from the position
					string position;
					
						cin >> position;
						x = position[0] - 'a';
						y = position[1] - '1';
						if (validPosition(x, y) ) {
							whitePlayer.remove_chess(x, y);
							blackPlayer.remove_chess(x, y);
							cout << board;
							
						}
						else {
							cout << "Invalid position. Please re-enter." << endl;
                            continue;
						}
					
				}else if (cmd == "=") { // makes it colour's turn to go next
					string colour; //black or white
					
						cin >> colour;
						if (colour == "white") {
							whiteTurn = 1;
							
						}
						else if (colour == "black"){
							whiteTurn = 0;
							
						}
						else{
							cout << "Invalid colour. Please re-enter." << endl;
                            continue;
						}
					
					
				}else {
					cout << "Bad setup symbol! Please re-input!" << endl;
				}
			}
		}
		else if (cmd == "game") {
			string player1; //human, computer[1-4]
			string player2;
			
				cin >> player1 >> player2;
				if (validPlayer(player1, player2)){
					whitePlayer.set_level(player1);
					blackPlayer.set_level(player2);
					if (!isSetup) {
						whitePlayer.clearPlayer();
						blackPlayer.clearPlayer();
						whitePlayer.set_default();
						blackPlayer.set_default();
						board.init();
					}
					isSetup = 0;
					gameStart = 1;
					cout << board;
					
				}
				else{
					cout << "Invalid Player type. Please re-enter player1 and player2." << endl;
                    continue;
				}
				
        
			

		}
		else if (cmd == "move") {
			bool success = 1;
			string move_cmd;
			string position;
			char promote;
			bool isPromote = 0;
			int x, y, x_new, y_new;
			
				getline(cin, move_cmd);
				istringstream ss{ move_cmd };
				ss >> position;
				x = position[0] - 'a';
				y = position[1] - '1';

				ss >> position;
				x_new = position[0] - 'a';
				y_new = position[1] - '1';
				
                if (ss >> promote) { isPromote = 1; }
                //move
                if (whiteTurn) {
                    if (whitePlayer.getLevel() == 0) { //human
                        if (validPosition(x, y) && validPosition(x_new, y_new)) {
                            if (isPromote) whitePlayer.human_move(x, y, x_new, y_new, &success, promote);
                            else whitePlayer.human_move(x, y, x_new, y_new, &success);
                            
                        }else{
                            cout << "Invalid positions. Please re-enter the positions." << endl;
                            continue;
                        }
                    }
                    else { //computer
                        whitePlayer.computer_move();
                        success = 1;
                    }
                    if (success) {
                        whiteTurn = 0;
                        cout << board;
                        if (blackPlayer.isCheck()) {
                  
                        	if (blackPlayer.isCheckmate()) {
	                            cout << "Checkmate! White wins!" << endl;
	                            score.setWhite(1);
	                            gameStart = 0;
	                            whiteTurn = 1;
                        	}
                        	else {
                        		cout << "Black is in check." << endl;
                        	}
                        	
                        }
                        
                        else if (blackPlayer.isStalemate()) {
                            cout << "Stalemate!" << endl;
                            score.setWhite(0.5);
                            score.setBlack(0.5);
                            gameStart = 0;
                            whiteTurn = 1;
                        } 
                    }
                }
                else {
                    if (blackPlayer.getLevel() == 0) { //human
                        if (validPosition(x, y) && validPosition(x_new, y_new)) {
                            if (isPromote) whitePlayer.human_move(x, y, x_new, y_new, &success, promote);
                            else blackPlayer.human_move(x, y, x_new, y_new, &success);
                            
                        
                        }
                        else{
                            cout << "Invalid positions. Please re-enter the positions." << endl;
                            continue;
                        }
                    }
                    else { //computer
                        blackPlayer.computer_move();
                        success = 1;
                    }
                    if (success) {
                        whiteTurn = 1;
                        cout << board;
                        if (whitePlayer.isCheck()) {
                        	
                      
                        	if (whitePlayer.isCheckmate()) {
	                            cout << "Checkmate! Black wins!" << endl;
	                            score.setBlack(1);
	                            gameStart = 0;
	                            whiteTurn = 1;
                            
                            }  
                            else {
                            	cout << "White is in check." << endl;
                            }
                        }
                        else if (whitePlayer.isStalemate()) {
                            cout << "Stalemate!" << endl;
                            score.setWhite(0.5);
                            score.setBlack(0.5);
                            gameStart = 0;
                            whiteTurn = 1;
                            
                        }
                    }
                }
                
            
				
			
		}
		else if (cmd == "resign"){
			if (whiteTurn) {
				cout << "Black wins!" << endl;
				score.setBlack(1);
			}
			else {
				cout << "White wins!" << endl;
				score.setWhite(1);
			}
			gameStart = 0;
			whiteTurn = 1;
		}
		else {
			cout << "Bad input!" << endl;
		}
	}
	} catch (ios::failure &) {
			cout << score.printScore(); //print final score

	}  // Any I/O failure quits
}
	






