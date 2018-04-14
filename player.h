#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include "board.h"
#include "piece.h"
#include "cell.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
class Player {
    bool isWhite;
    std::vector<std::shared_ptr<Piece>> chess;
    Player *p2 = nullptr;
    int level = 0;
    int numAlive = 0;
    std::shared_ptr<Piece> lastMovePawn = nullptr;  //possible en passent
    Board *b;
public:
    Player(bool isWhite, Board *b) : isWhite{ isWhite }, b{ b } {}
   // ~Player() { delete p2; delete b;}
    //get and set
    void set_player(Player *p2);
    void reduce_numAlive(); //reduce by one
    int get_numAlive();
    std::vector<std::shared_ptr<Piece>> &get_chess();
    void set_level(std::string player);
    int getLevel();
    std::shared_ptr<Piece> get_lastMovePawn();
    //set up
    void clearPlayer();
    bool setup();
    void set_default(); //default pieces
    void add_chess(char c, int x, int y);
    void remove_chess(int x, int y);
    //move
    void capture(int x, int y);
    void castling(int new_x, int new_y, bool *s);//this func can only be used by human_move
    void human_move(int x, int y, int x_new, int y_new, bool *success, char promote = 'z');
    void move_random_piece();//helper function for computer move
    void try_attack(); //helper for level2
    bool predict_capture(int x, int y); //if position x y will be captured by any opponent chess
    void computer_move();
    //check, checkmate, stalemate
    bool isCheck();
    bool isCheck2(int x, int y);
    bool noCheckAfterMove(std::shared_ptr<Piece> p);
    bool checkAfterMove(std::shared_ptr<Piece> p, int x, int y);
    bool isCheckmate();
    bool ifCastling(std::shared_ptr<Piece> k, std::shared_ptr<Piece> r);
    bool isStalemate();
    bool ischeck3(int x, int y);
    bool ischeck4();
    void try_attack2(int a);
};
static bool sortBypower( Piece *p1,  Piece *p2);
#endif


