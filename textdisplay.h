#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

const int boardSize = 8; // 8 x 8 board
const char empty = 'Z'; //cell with no piece


class TextDisplay {
  std::vector<std::vector<char>> theDisplay;

 public:
  TextDisplay();

  void notify(char cell, int x, int y);

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif


