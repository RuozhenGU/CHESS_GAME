#include <iostream>
#include <memory>
#include <string>
#include "player.h"
#include <cstdlib>


using namespace std;
void Player::set_player(Player *p2) {
    this->p2 = p2;
}
void Player::reduce_numAlive() {
    --numAlive;
}
int Player::get_numAlive() {
    return numAlive;
}
vector<shared_ptr<Piece>> &Player::get_chess() {
    return chess;
}

void Player::set_level(string player) {
    if (player == "human") {
        level = 0;
    }
    else if (player == "computer[1]"){
        level = 1;
    }
    else if (player == "computer[2]"){
        level = 2;
    }
    else if (player == "computer[3]"){
        level = 3;
    }
    else if (player == "computer[4]"){
        level = 4;
    }
    else {
        cout << "Invalid player" << endl;
    }
}

int Player::getLevel() { return level; }

std::shared_ptr<Piece> Player::get_lastMovePawn() { return lastMovePawn; }

void Player::clearPlayer() {
    chess.clear(); //clear pieces
}

bool Player::setup() {
    int numking = 0;
    for (unsigned int i = 0; i < chess.size(); ++i) {
        if (chess[i]->get_name() == 'k' || chess[i]->get_name() == 'K') ++numking;
    }
    if (numking < 1) {
        cout << "No king!" << endl;
        return false;
    }
    if (isCheck()) {
        cout << "King is in check!" << endl;
        return false;
    }
    return true;
}

void Player::set_default(){
    
    if (isWhite == true){
        shared_ptr<Piece> p1(new Rook{ 0, 0, true, 'R', b });
        shared_ptr<Piece> p2(new Knight{ 1, 0, true, 'N', b });
        shared_ptr<Piece> p3(new Bishop{ 2, 0, true, 'B', b });
        shared_ptr<Piece> p4(new Queen{ 3, 0, true, 'Q', b });
        shared_ptr<Piece> p5(new King{ 4, 0, true, 'K', b });
        shared_ptr<Piece> p6(new Bishop{ 5, 0, true, 'B', b });
        shared_ptr<Piece> p7(new Knight{ 6, 0, true, 'N', b });
        shared_ptr<Piece> p8(new Rook{ 7, 0, true, 'R', b });
        chess.emplace_back(p1);
        chess.emplace_back(p2);
        chess.emplace_back(p3);
        chess.emplace_back(p4);
        chess.emplace_back(p5);
        chess.emplace_back(p6);
        chess.emplace_back(p7);
        chess.emplace_back(p8);
        for (int i = 0; i < 8; ++i){
            shared_ptr<Piece> p(new Pawn{ i, 1, true, 'P', b });
            chess.emplace_back(p);
        }
        
    }
    else{
        shared_ptr<Piece> p1(new Rook{ 0, 7, true, 'r', b });
        shared_ptr<Piece> p2(new Knight{ 1, 7, true, 'n', b });
        shared_ptr<Piece> p3(new Bishop{ 2, 7, true, 'b', b });
        shared_ptr<Piece> p4(new Queen{ 3, 7, true, 'q', b });
        shared_ptr<Piece> p5(new King{ 4, 7, true, 'k', b });
        shared_ptr<Piece> p6(new Bishop{ 5, 7, true, 'b', b });
        shared_ptr<Piece> p7(new Knight{ 6, 7, true, 'n', b });
        shared_ptr<Piece> p8(new Rook{ 7, 7, true, 'r', b });
        chess.emplace_back(p1);
        chess.emplace_back(p2);
        chess.emplace_back(p3);
        chess.emplace_back(p4);
        chess.emplace_back(p5);
        chess.emplace_back(p6);
        chess.emplace_back(p7);
        chess.emplace_back(p8);
        for (int i = 0; i < 8; ++i){
            shared_ptr<Piece> p(new Pawn{ i, 6, true, 'p', b });
            chess.emplace_back(p);
        }
    }
    /*for(unsigned int i = 0; i < chess.size(); ++i) {
     cout << chess[i]->get_name() << chess[i]->getX() << chess[i]->getY() << endl;
     } */
    
    numAlive = 16;
}

void Player::add_chess(char c, int x, int y){ //use for loop to call this function
    bool K_exist = false;
    if(b->get_cell(x, y)->get_occupied() != 'Z') {
        cout << "Already occupied here!" << endl;
        return;
    }
    if (c == 'K' || c == 'k'){
        //check if king is exist
        for (unsigned int i = 0; i < chess.size(); i++) {
            if (chess[i]->get_name() == 'K' || chess[i]->get_name() == 'k'){
                K_exist = true;
            }
        }
        if (K_exist == false){
            shared_ptr<Piece> p(new King{ x, y, true, c, b });
            chess.emplace_back(p);
            b->place(c, x, y);
            ++numAlive;
        }
        else{
            cout << "King already exist." << endl;
            return;
        }
    }
    else if (c == 'Q' || c == 'q'){
        shared_ptr<Piece> p(new Queen{ x, y, true, c, b });
        chess.emplace_back(p);
        b->place(c, x, y);
        ++numAlive;
    }
    
    else if (c == 'B' || c == 'b'){
        shared_ptr<Piece> p(new Bishop{ x, y, true, c, b });
        chess.emplace_back(p);
        b->place(c, x, y);
        ++numAlive;
    }
    else if (c == 'R' || c == 'r'){
        shared_ptr<Piece> p(new Rook{ x, y, true, c, b });
        chess.emplace_back(p);
        b->place(c, x, y);
        ++numAlive;
    }
    else if (c == 'N' || c == 'n'){
        shared_ptr<Piece> p(new Knight{ x, y, true, c, b });
        chess.emplace_back(p);
        b->place(c, x, y);
        ++numAlive;
    }
    else if (c == 'P' || c == 'p'){
        if (y != 0 and y != 7){
            shared_ptr<Piece> p(new Pawn{ x, y, true, c, b });
            chess.emplace_back(p);
            b->place(c, x, y);
            ++numAlive;
        }
        else{
            cout << "Pawn cannot be in the first row and last row." << endl;
            return;
        }
    }
}


void Player::remove_chess(int x, int y){
    if(b->get_cell(x, y)->get_occupied() == 'Z') {
        cout << "Empty cell!" << endl;
        return;
    }
    for (unsigned int i = 0; i < chess.size(); i++) {
        if (chess[i]->getX() == x && chess[i]->getY() == y){
            chess.erase(chess.begin() + i);
            b->remove(x, y);
            --numAlive;
        }
    }
}


void Player::capture(int x, int y) { //capture player2's chess
    for (unsigned int index = 0; index < p2->get_chess().size(); index++) {
        if (p2->get_chess()[index]->getX() == x && p2->get_chess()[index]->getY() == y) {
            p2->get_chess()[index]->SetAlive();//this piece die
            p2->reduce_numAlive();
            p2->get_chess().erase(p2->get_chess().begin() + index);
            b->place('Z', x, y);
        }
    }
}
//premise: king is never moeved
void Player::castling(int new_x, int new_y, bool *s) {
    for (unsigned int index = 0; index < chess.size(); index++) {
        if (chess[index]->get_name() == 'r' || chess[index]->get_name() == 'R') {
            if (chess[index]->getX() - new_x == 1 || chess[index]->getX() - new_x == -2) {//find target rook from two
                if (chess[index]->getX() - chess[index]->getX_prev() == 0 && //make sure rook is on first move
                    chess[index]->getY() - chess[index]->getY_prev() == 0) {
                    if (chess[index]->isblock(4, 0) == false) {//nothing block, save to perform castling
                        *s = true;
                        chess[index]->SetX_prev(chess[index]->getX());
                        if (chess[index]->getX() > 4) chess[index]->SetX(5);
                        if (chess[index]->getX() < 4) chess[index]->SetX(3);
                        b->place(chess[index]->get_name(), chess[index]->getX(), chess[index]->getY());
                        b->place('Z', chess[index]->getX_prev(), chess[index]->getY_prev());
                        chess[index]->produce_next();
                        return;
                    }
                }
            }
        }
    }
    if (*s == false) {
        cout << "You cannot perform castling! please move again." << endl;
    }
}

// note to call this function, if flag is false, call again(loop)
void Player::human_move(int x, int y, int x_new, int y_new, bool *success, char promote) { //ptr

    //cout << b->get_cell(2,5)->get_occupied() << endl;
    if (promote == 'k' || promote == 'K') {
        cout << "You cannot promote king! please move again" << endl;
        *success = false;
        return;
    }

    char c = b->get_cell(x, y)->get_occupied();

    //check if move a empty cell
    if (c == 'Z') {
        cout << "You cannot move an empty piece! Please move again." << endl;
        *success = false;
        return;
    }

    for (auto it = chess.begin(); it != chess.end(); it++) {
        if ((*it)->getX() == x && (*it)->getY() == y) { //find piece that need to be moved

            //special condition to perfrom castling first
            if (c == 'K' || c == 'k') {
                if (x_new - x == 2 || x_new - x == -2) {
                    if ((*it)->getX() - (*it)->getX_prev() == 0 && (*it)->getY() - (*it)->getY_prev() == 0
                        && isCheck() == false && isCheck2(x_new, y_new) == false) {
                        bool s = false;//true is success, then we mutate king as well
                        castling(x_new, y_new, &s);//note king is on first move now
                        if (s == true) {
                            (*it)->SetX_prev(4);
                            (*it)->SetX(x_new);
                            b->place((*it)->get_name(), (*it)->getX(), (*it)->getY());
                            b->place('Z', (*it)->getX_prev(), (*it)->getY_prev());
                            (*it)->produce_next();
                            *success = true; 
                            return;
                        }
                        else {
                            *success = false;
                            return;
                        }
                    }
                    else {
                        *success = false;
                        cout << "This castling is invalid! please move again." << endl;
                        return;
                    }
                }
            }  //finish performing castling

            //check whether this move is valid 
            bool canMove = 0;
            for (unsigned int i = 0; i < (*it)->getNext_move().size(); ++i) {
                if ((*it)->getNext_move()[i][0] == x_new && (*it)->getNext_move()[i][1] == y_new) {
                    canMove = 1;
                    //cout << b->get_cell(2,5)->get_occupied() << endl;
                    break;
                }
            }
            if (!canMove) {
                cout << "Invalid move! Please move again." << endl;
                *success = false;
                return;
            }
            

            //check if the move will be blocked
            if ((c == 'p' || c == 'P') && x == x_new && b->check_occupied(x_new, y_new)) {
                cout << "You are blocked to move to the target position! Please move again." << endl;
                *success = false;
                return;
            }
            if ((*it)->isblock(x_new, y_new) == true) {
                cout << "You are blocked to move to the target position! Please move again." << endl;
                *success = false;
                return;
            }

            //check if the destination position has your own piece
            if (b->check_occupied(x_new, y_new) == true
                && b->get_cell(x_new, y_new)->isWhite() == isWhite) {
                //cout << b->get_cell(x_new, y_new)->get_occupied() << endl; 
                cout << "The destination position has one of you chess! please move again." << endl;
                *success = false;
                return;
            }

            //check if king will be in check after move
            if (checkAfterMove(*it, x_new, y_new)) {
                cout << "Moving this chess will put your king in check! Please move again." << endl;
                *success = false;
                return;
            }


            //special capture if piece is pawn;
           if ((c == 'P' && y == 4) || (c == 'p' && y == 3)) { //pawn is in fifth rank
                if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == x_new) {

                    //last move is other player's pawn and it first move 2 sqaures
                    b->place(c, x_new, y_new);
                    b->place('Z', x, y);
                    (*it)->produce_next();
                    capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                    return;
                }
            } 
            if ((c == 'p' || c == 'P') && x != x_new && !b->check_occupied(x_new, y_new)) {
                cout << "Invalid move! Please move again." << endl;
                *success = false;
                return;
            }

            //check if can capture
            if (b->check_occupied(x_new, y_new) == true) { //capture
                capture(x_new, y_new); // clear the destination cell
            }

            //move piece to destination and clear the old position
            (*it)->SetX_prev(x);
            (*it)->SetX_prev(y);
            (*it)->SetX(x_new);
            (*it)->SetY(y_new);
            b->place(c, x_new, y_new);
            b->place('Z', x, y);
            (*it)->produce_next();
            *success = true;

            //possible captured pawn for en passent
            if ((c == 'P' || c == 'p')
                && (y_new - y == 2 || y_new - y == -2) && (x_new == x)) {
                lastMovePawn = *it;
            }
            else {
                lastMovePawn = nullptr;
            }

            // if promote
            if (c == 'p' || c == 'P') {
                if ((isWhite == true && y_new == 7) || (isWhite == false && y_new == 0)) {
                    remove_chess(x_new, y_new);
                    add_chess(promote, x_new, y_new); //promote is not king
                }
            }

            return;

        }

    }
    cout << "You cannot move other player's piece! Please move again." << endl;
    *success = false;
    return;
}



bool Player::isCheck(){
    for (unsigned int i = 0; i < chess.size(); ++i) {
        if (chess[i]->get_name() == 'k' || chess[i]->get_name() == 'K') { //chess is king
            int x = chess[i]->getX();
            int y = chess[i]->getY();

            if (isCheck2(x, y)) return true;
        }
    }
    return false;
}

bool Player::isCheck2(int x, int y) { //true if king in (x,y) is in check, false otherwise
    for (unsigned int i = 0; i < p2->get_chess().size(); ++i) {//assume all cheess in peice are alive
        if (p2->get_chess()[i]->getAlive() && p2->get_chess()[i]->attack(x, y)) { //piece is alive
            if (!p2->get_chess()[i]->isblock(x, y)) return true;
        }
    }
    return false;
}

bool Player::noCheckAfterMove(std::shared_ptr<Piece> p) { //return true if k won't be in check after p moves, otherwise false
    
    for (unsigned int i = 0; i < p->getNext_move().size(); ++i) {
        int x = p->getNext_move()[i][0];
        int y = p->getNext_move()[i][1];
        char c = p->get_name();
        //invalid move
        if ((c == 'p' || c == 'P') && p->getX() != x && !b->check_occupied(x, y)) continue;
        if ((c == 'p' || c == 'P') && x == p->getX() && b->check_occupied(x, y)) continue;
        if (p->isblock(x, y)) continue;
        if (b->check_occupied(x, y) && b->get_cell(x, y)->isWhite() == isWhite) continue;
        //ok
        if(!checkAfterMove(p, p->getNext_move()[i][0], p->getNext_move()[i][1])) {
            return true;
        }
    }
    
    return false;
} 

bool Player::checkAfterMove(std::shared_ptr<Piece> p, int x, int y) { //true if your king will be in check after move
    //(x,y) is piece's move destination
    //assume p will be not block to move to (x,y), or has same color piece on (x,y)
    //assume x, y is a possible move or capture
    bool check = false;
    if(isCheck()) check = true;
    char c = p->get_name();

    //i move a piece, if i am in check will it block other's attack? if yes, check is false
    // or move this piece will it let my king under other's attack? if yes, check is true

    //move piece
    if(c == 'k' || c == 'K') {
        if(isCheck2(x, y)) check = true;
        else check = false;
    } else {
        char temp_c =  b->get_cell(x,y)->get_occupied();
        b->get_cell(x, y)->set_occupied(c);   
        b->get_cell(p->getX(), p->getY())->set_occupied('Z');

        if(isCheck()) {
                check = true; 
        } 
        else {
            check = false; 
        }
        
        //restore piece
        b->get_cell(x, y)->set_occupied(temp_c); 
        b->get_cell(p->getX(), p->getY())->set_occupied(c);

    }
    

    int king_x;
    int king_y;
    for(unsigned int i = 0; i < chess.size(); ++i) { //find king's position
            if(chess[i]->get_name() == 'k' || chess[i]->get_name() == 'K') {
                    king_x = chess[i]->getX();
                    king_y = chess[i]->getY();
            }
    }
    for(unsigned int j = 0; j < p2->chess.size(); ++j) {
        if(p2->chess[j]->getX() == x && p2->chess[j]->getY() == y) { //if can capture a piece
                if(p2->get_chess()[j]->attack(king_x, king_y)) {
                    //if this captured piece is attacking my king, then i capture it will prevent my king being check
                    check = false;
                }
                
        }
    }
    //if can't block or can't capture a piece to prevent king in check, check is still true
    if(check) return true;
    return false;
}



bool Player::isCheckmate() {
    if (!isCheck()) return false; //king is not in check
    //king is in check, is any possible way to move king or other piece to let king will not be in check?
    for (unsigned int i = 0; i < chess.size(); ++i) {
        if (noCheckAfterMove(chess[i])) return false;
        
    } 
    return true;
}

bool Player::ifCastling(std::shared_ptr<Piece> k, std::shared_ptr<Piece> r) { //return true if k and rook can castling, otherwise false
    if (k->getX() != k->getX_prev() || k->getY() != k->getY_prev()) return false; //king has been moved
    if (r->getX() != r->getX_prev() || r->getY() != r->getY_prev()) return false; //rook has been moved
    int x = k->getX();
    int y = k->getY();
    if (r->isblock(x, y)) return false; //there are pieces standing bewteen the king and rook
    if (isCheck2(x, y)) return false; // king is in check
    x = x < r->getX() ? x + 2 : x - 2; //king's position after castling
    if (isCheck2(x, y)) return false; // king will be in check after castling
    return true;
}

bool Player::isStalemate() {
    if (isCheck()) return false; // king is in check
    for (unsigned int i = 0; i < chess.size(); ++i) {
        //if (chess[i]->getAlive()) { //all alive pieces
            //piece is king
            if (chess[i]->get_name() == 'k' || chess[i]->get_name() == 'K') {
                for (unsigned int j = 0; j < chess[i]->getNext_move().size(); ++j) {
                    //king can move to a cell that not in check
                    if (!isCheck2(chess[i]->getNext_move()[j][0], chess[i]->getNext_move()[j][1])) return false;
                }
                for (unsigned int k = 0; k < chess.size(); ++k) {
                    if ((chess[k]->get_name() == 'r' || chess[k]->get_name() == 'R')
                        && chess[k]->getAlive() && ifCastling(chess[i], chess[k])) {
                        return false; //can castling
                    }
                }
            }
            //cout << "here4" << endl;
            //other piece except king
            else if (noCheckAfterMove(chess[i])) return false;
            //whether piece can move to a cell that not let k in check
        //}
    }
    return true;
}



bool Player::ischeck3(int x, int y) {
    for (unsigned int i = 0; i < p2->get_chess().size(); ++i) {//assume all cheess in peice are alive
        if (p2->get_chess()[i]->getAlive() && p2->get_chess()[i]->attack(x, y)) { //piece is alive
            if(b->get_cell(p2->get_chess()[i]->getX(),p2->get_chess()[i]->getY())->isWhite() == p2->isWhite) {
                if (!p2->get_chess()[i]->isblock(x, y)) return true;
            }
        }
    }
    return false;
}

bool Player::ischeck4() {
    for (unsigned int i = 0; i < chess.size(); ++i) {
        if (chess[i]->get_name() == 'k' || chess[i]->get_name() == 'K') { //chess is king
            int x = chess[i]->getX();
            int y = chess[i]->getY();
            
            if (ischeck3(x, y)) return true;
        }
    }
    return false;
}


void Player::move_random_piece() {
    for (unsigned int j = 0; j < chess.size(); j++) {
        for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
            if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
            if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                b->check_occupied((*it)[0], (*it)[1]) == true)
                continue;
            if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') 
                && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z' &&(*it)[0] != chess[j]->getX()) continue;
            //capture
            int temp_x = chess[j]->getX_prev();
            int temp_y = chess[j]->getX_prev();
            chess[j]->SetX_prev(chess[j]->getX());
            chess[j]->SetY_prev(chess[j]->getY());
            chess[j]->SetX((*it)[0]);
            chess[j]->SetY((*it)[1]);
            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
            if (ischeck4() == true) {//moving this wont help anything
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                    //last move is other player's pawn and it first move 2 sqaures
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    chess[j]->produce_next();
                    capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                    return;
                }
            }
            if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                capture((*it)[0], (*it)[1]);
            }
            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            //b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
            //b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            chess[j]->produce_next();
            //if pawn moves for two steps, record it
            if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                && (chess[j]->getY() - chess[j]->getY_prev() == 2 || chess[j]->getY() - chess[j]->getY_prev() == -2)
                && (chess[j]->getX() == chess[j]->getX_prev())) {
                lastMovePawn = chess[j];
            } else {
                lastMovePawn = nullptr;
            }
            if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                    remove_chess(chess[j]->getX(), chess[j]->getY());
                    if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A') add_chess('Q',chess[j]->getX() , chess[j]->getY());
                    if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a') add_chess('q',chess[j]->getX() , chess[j]->getY());
                    p2->isCheck();
                    p2->isCheckmate();
                }
            }
            return;
        }
    }
}
void Player::try_attack() {
    for (unsigned int j = 0; j < chess.size(); j++) {
        for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
            if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
            if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                b->check_occupied((*it)[0], (*it)[1]) == true)
                continue;
            if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') 
                && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z'&&(*it)[0] != chess[j]->getX()) continue;
            int temp_x = chess[j]->getX_prev();
            int temp_y = chess[j]->getX_prev();
            chess[j]->SetX_prev(chess[j]->getX());
            chess[j]->SetY_prev(chess[j]->getY());
            chess[j]->SetX((*it)[0]);
            chess[j]->SetY((*it)[1]);
            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
            if (ischeck4() == true) {//moving this wont help anything
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            //no check no capture
            if (p2->isCheck() == false && b->check_occupied((*it)[0], (*it)[1]) == false) {
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                    //last move is other player's pawn and it first move 2 sqaures
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    chess[j]->produce_next();
                    capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                    return;
                }
            }
            if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0]){
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                capture((*it)[0], (*it)[1]);
            } /*else { //move not attack
                if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') &&
                    chess[j]->getX_prev() != chess[j]->getX()) {
                    b->place('Z', (*it)[0], (*it)[1]);
                    b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                    chess[j]->SetX(chess[j]->getX_prev());
                    chess[j]->SetY(chess[j]->getY_prev());
                    chess[j]->SetX_prev(temp_x);
                    chess[j]->SetX_prev(temp_y);
                    continue;
                }
            }
            */
            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            chess[j]->produce_next();
            //if pawn moves for two steps, record it
            if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                && (chess[j]->getY() - chess[j]->getY_prev() == 2 || chess[j]->getY() - chess[j]->getY_prev() == -2)
                && (chess[j]->getX() == chess[j]->getX_prev())) {
                lastMovePawn = chess[j];
            } else {
                lastMovePawn = nullptr;
            }
            if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                    remove_chess(chess[j]->getX(), chess[j]->getY());
                    if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A') add_chess('Q',chess[j]->getX() , chess[j]->getY());
                    if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a') add_chess('q',chess[j]->getX() , chess[j]->getY());
                }
            }
            return;
        }
    }
    //if here, means no capturing exist, just perform a random move
    move_random_piece();
}
void Player::try_attack2(int a) {
    for (unsigned int j = 0; j < chess.size(); j++) {
        if(chess[j]->get_power()!=a) continue;
        for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
            if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
            if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                b->check_occupied((*it)[0], (*it)[1]) == true)
                continue;
            if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') 
                && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z'&&(*it)[0] != chess[j]->getX()) continue;
            int temp_x = chess[j]->getX_prev();
            int temp_y = chess[j]->getX_prev();
            chess[j]->SetX_prev(chess[j]->getX());
            chess[j]->SetY_prev(chess[j]->getY());
            chess[j]->SetX((*it)[0]);
            chess[j]->SetY((*it)[1]);
            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
            if (ischeck4() == true) {//moving this wont help anything
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            //no check no capture
            if (p2->isCheck() == false && b->check_occupied((*it)[0], (*it)[1]) == false) {
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                    //last move is other player's pawn and it first move 2 sqaures
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    chess[j]->produce_next();
                    capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                    return;
                }
            }
            if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                capture((*it)[0], (*it)[1]);
            }
            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            chess[j]->produce_next();
            //if pawn moves for two steps, record it
            if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                && (chess[j]->getY() - chess[j]->getY_prev() == 2 || chess[j]->getY() - chess[j]->getY_prev() == -2)
                && (chess[j]->getX() == chess[j]->getX_prev())) {
                lastMovePawn = chess[j];
            } else {
                lastMovePawn = nullptr;
            }
            if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                    remove_chess(chess[j]->getX(), chess[j]->getY());
                    if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A') add_chess('Q',chess[j]->getX() , chess[j]->getY());
                    if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a') add_chess('q',chess[j]->getX() , chess[j]->getY());
                }
            }
            return;
        }
    }
    for (unsigned int j = 0; j < chess.size(); j++) {
        if(chess[j]->get_power()!=a) continue;
        for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
            if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
            if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                b->check_occupied((*it)[0], (*it)[1]) == true)
                continue;
            if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') 
                && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z' &&(*it)[0] != chess[j]->getX()) continue;
            //capture
            int temp_x = chess[j]->getX_prev();
            int temp_y = chess[j]->getX_prev();
            chess[j]->SetX_prev(chess[j]->getX());
            chess[j]->SetY_prev(chess[j]->getY());
            chess[j]->SetX((*it)[0]);
            chess[j]->SetY((*it)[1]);
            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
            if (ischeck4() == true) {//moving this wont help anything
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                    //last move is other player's pawn and it first move 2 sqaures
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    chess[j]->produce_next();
                    capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                    return;
                }
            }
            if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                b->place('Z', (*it)[0], (*it)[1]);
                b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                chess[j]->SetX(chess[j]->getX_prev());
                chess[j]->SetY(chess[j]->getY_prev());
                chess[j]->SetX_prev(temp_x);
                chess[j]->SetY_prev(temp_y);
                continue;
            }
            if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                capture((*it)[0], (*it)[1]);
            }
            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            //b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
            //b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
            chess[j]->produce_next();
            //if pawn moves for two steps, record it
            if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                && (chess[j]->getY() - chess[j]->getY_prev() == 2 || chess[j]->getY() - chess[j]->getY_prev() == -2)
                && (chess[j]->getX() == chess[j]->getX_prev())) {
                lastMovePawn = chess[j];
            } else {
                lastMovePawn = nullptr;
            }
            if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                    remove_chess(chess[j]->getX(), chess[j]->getY());
                    if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A') add_chess('Q',chess[j]->getX() , chess[j]->getY());
                    if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a') add_chess('q',chess[j]->getX() , chess[j]->getY());
                    p2->isCheck();
                    p2->isCheckmate();
                }
            }
            return;
        }
    }}
bool Player::predict_capture(int x, int y) {
    for (auto it = p2->get_chess().begin(); it != p2->get_chess().end(); it++) {
        if ((*it)->attack(x, y) == true) return true;
    }
    return false;
}
bool sortBypower( Piece *p1,  Piece *p2) { return p1->get_power() > p2->get_power(); }
int global_a=5;
void Player::computer_move() {   //computer will move based on the level
    if (level == 1) { //whichever can move, move it
        //note it does not matter whether im in check or not
        move_random_piece();
        return;
    }
    else if (level == 2) {
        try_attack();
        return;
    }
    else if (level == 3) {
        //first loop to see if there is any chess which might be captured at nexg step, move it first
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z'&&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
        }
        //if the code reaches here, that means we cannot avoid capturing, lets try to attach, or just randomly move sth
        try_attack();
    }
    else if (level == 4) {
        int cast = 0;
        for(int m =0; m < p2->get_chess().size(); m++){
            if ((p2->get_chess()[m]->get_name() == 'q' || p2->get_chess()[m]->get_name() == 'Q')
                && (p2->get_chess()[m]->getX() == 3 || p2->get_chess()[m]->getX() == 5)) {
                for (int n = 0; n < chess.size(); n++) {
                    if (chess[n]->get_name() == 'K' || chess[n]->get_name() == 'k') {
                        for (auto it = chess[n]->getNext_move().begin(); it != chess[n]->getNext_move().end(); it++) {
                            int x_new = (*it)[0];
                            int y_new = (*it)[0];
                            int x = chess[n]->getX();
                            int y = chess[n]->getY();
                            if (x_new - x == 2 || x_new - x == -2) {
                                if (chess[n]->getX() - chess[n]->getX_prev() == 0 &&
                                    chess[n]->getY() - chess[n]->getY_prev() == 0
                                    && isCheck() == false && isCheck2(x_new, y_new) == false) {
                                    bool s = false;//true is success, then we mutate king as well
                                    castling(x_new, y_new, &s);//note king is on first move now
                                    if (s == true) {
                                        chess[n]->SetX_prev(4);
                                        chess[n]->SetX(x_new);
                                        b->place(chess[n]->get_name(), chess[n]->getX(), chess[n]->getY());
                                        b->place('Z', chess[n]->getX_prev(), chess[n]->getY_prev());
                                        chess[n]->produce_next();
                                        return;
                                    } else {
                                        break;
                                    }
                                } else {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (global_a >0) {
            global_a--;
            for (int i = 0; i < chess.size(); i++) {
                if(isCheck()) {
                    if (chess[i]->get_name() == 'k' || chess[i]->get_name() == 'K'){
                        chess[i]->set_power(8);
                        continue;
                    }
                }
                if ((chess[i]->get_name() == 'p' || chess[i]->get_name() == 'P')
                    && chess[i]->getX() == 3
                    && (chess[i]->getY() == 1 || chess[i]->getY() == 6)) {
                    chess[i]->set_power(8);
                    continue;
                }
                if (chess[i]->get_name() == 'q' || chess[i]->get_name() == 'Q') {
                    chess[i]->set_power(7);
                    continue;
                }
                if ((chess[i]->get_name() == 'n' || chess[i]->get_name() == 'N')
                    && (chess[i]->getY() <= 2 || chess[i]->getY() >= 5)) {
                    chess[i]->set_power(6);
                    continue;
                } else if (chess[i]->get_name() == 'n' || chess[i]->get_name() == 'N') {
                    chess[i]->set_power(3);
                    continue;
                }
                if (chess[i]->get_name() == 'r' || chess[i]->get_name() == 'R') chess[i]->set_power(5);
                if (chess[i]->get_name() == 'b' || chess[i]->get_name() == 'B') chess[i]->set_power(4);
                if (chess[i]->get_name() == 'p' || chess[i]->get_name() == 'P') chess[i]->set_power(2);
                if (chess[i]->get_name() == 'k' || chess[i]->get_name() == 'K') chess[i]->set_power(1);
            }
        } else {
            for (int i = 0; i < chess.size(); i++) {
                if (chess[i]->get_name() == 'q' || chess[i]->get_name() == 'Q') {
                    chess[i]->set_power(rand() % 9);
                    continue;
                }
                if ((chess[i]->get_name() == 'n' || chess[i]->get_name() == 'N')
                    && (chess[i]->getY() <= 2 || chess[i]->getY() >= 5)) {
                    chess[i]->set_power(rand() % 9);
                    continue;
                } else if (chess[i]->get_name() == 'n' || chess[i]->get_name() == 'N') {
                    chess[i]->set_power(rand() % 9);
                    continue;
                }
                if (chess[i]->get_name() == 'r' || chess[i]->get_name() == 'R') chess[i]->set_power(rand() % 9);
                if (chess[i]->get_name() == 'b' || chess[i]->get_name() == 'B') chess[i]->set_power(rand() % 9);
                if (chess[i]->get_name() == 'p' || chess[i]->get_name() == 'P') chess[i]->set_power(rand() % 9);
                if (chess[i]->get_name() == 'k' || chess[i]->get_name() == 'K') chess[i]->set_power(rand() % 9);
            }
        }
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (chess[j]->get_power()!=8) continue;
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z'&&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
            try_attack2(8);
            return;
        }
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (chess[j]->get_power()!=7) continue;
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z'&&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
            try_attack2(7);
            return;
        }
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (chess[j]->get_power()!=6) continue;
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z'&&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
            try_attack2(6);
            return;
        }
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (chess[j]->get_power()!=5) continue;
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z'&&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
            try_attack2(5);
            return;
        }
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (chess[j]->get_power()!=4) continue;
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z' &&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
            try_attack2(4);
            return;
        }
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (chess[j]->get_power()!=3) continue;
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z' &&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
            try_attack2(3);
            return;
        }
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (chess[j]->get_power()!=2) continue;
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z'&&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
            try_attack2(2);
            return;
        }
        for (unsigned int j = 0; j < chess.size(); j++) {
            if (chess[j]->get_power()!=1) continue;
            if (predict_capture(chess[j]->getX(), chess[j]->getY()) == true) {
                //we need to move this piece to avoid capturing
                for (auto it = chess[j]->getNext_move().begin(); it != chess[j]->getNext_move().end(); it++) {
                    if (predict_capture((*it)[0], (*it)[1]) == true)
                        continue;//,must can avoid caputuing and then we do the rest
                    if (chess[j]->isblock((*it)[0], (*it)[1]) == true) continue; //make sure its not blocked
                    if (b->get_cell((*it)[0], (*it)[1])->isWhite() == isWhite &&
                        b->check_occupied((*it)[0], (*it)[1]) == true)
                        continue;
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P')
                        && b->get_cell((*it)[0],(*it)[1])->get_occupied() == 'Z' &&(*it)[0] != chess[j]->getX()) continue;
                    int temp_x = chess[j]->getX_prev();
                    int temp_y = chess[j]->getX_prev();
                    chess[j]->SetX_prev(chess[j]->getX());
                    chess[j]->SetY_prev(chess[j]->getY());
                    chess[j]->SetX((*it)[0]);
                    chess[j]->SetY((*it)[1]);
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                    if (ischeck4() == true) {//moving this wont help anything
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if ((chess[j]->get_name() == 'P' && chess[j]->getY() == 4) ||
                        (chess[j]->get_name() == 'p' && chess[j]->getY() == 3)) { //pawn is in fifth rank
                        if (p2->get_lastMovePawn() != nullptr && p2->get_lastMovePawn()->getX() == (*it)[0]) {
                            //last move is other player's pawn and it first move 2 sqaures
                            b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                            b->place('Z', chess[j]->getX_prev(), chess[j]->getY_prev());
                            chess[j]->produce_next();
                            capture(p2->get_lastMovePawn()->getX(), p2->get_lastMovePawn()->getY());
                            return;
                        }
                    }
                    if ((chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') && chess[j]->getX_prev() != (*it)[0] && !b->check_occupied((*it)[0],(*it)[1])){
                        b->place('Z', (*it)[0], (*it)[1]);
                        b->place(chess[j]->get_name(), chess[j]->getX_prev(), chess[j]->getY_prev());
                        chess[j]->SetX(chess[j]->getX_prev());
                        chess[j]->SetY(chess[j]->getY_prev());
                        chess[j]->SetX_prev(temp_x);
                        chess[j]->SetY_prev(temp_y);
                        continue;
                    }
                    if (b->check_occupied((*it)[0], (*it)[1]) == true) { //capture
                        capture((*it)[0], (*it)[1]);
                    }
                    b->place(chess[j]->get_name(), (*it)[0], (*it)[1]);
                    chess[j]->produce_next();
                    //if pawn moves for two steps, record it
                    if ((chess[j]->get_name() == 'P' || chess[j]->get_name() == 'p')
                        && (chess[j]->getY() - chess[j]->getY_prev() == 2 ||
                            chess[j]->getY() - chess[j]->getY_prev() == -2)
                        && (chess[j]->getX() == chess[j]->getX_prev())) {
                        lastMovePawn = chess[j];
                    } else {
                        lastMovePawn = nullptr;
                    }
                    if (chess[j]->get_name() == 'p' || chess[j]->get_name() == 'P') {
                        if ((isWhite == true && chess[j]->getY() == 7) || (isWhite == false && chess[j]->getY() == 0)) {
                            remove_chess(chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'Z' && chess[j]->get_name() > 'A')
                                add_chess('Q', chess[j]->getX(), chess[j]->getY());
                            if (chess[j]->get_name() < 'z' && chess[j]->get_name() > 'a')
                                add_chess('q', chess[j]->getX(), chess[j]->getY());
                        }
                    }
                    return;
                }
            }
            try_attack2(1);
            return;
        }
        //if the code reaches here, that means we cannot avoid capturing, lets try to attach, or just randomly move sth
    }
}
