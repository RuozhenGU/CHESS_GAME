#ifndef GRAPHICALDISPLAY_H
#define GRAPHICALDISPLAY_H
#include <cstddef>
#include <memory>
#include <iostream>
#include <vector>
#include "window.h"

class Xwindow;
class GraphicalDisplay{
  Xwindow xw{520,520};

 public:
  GraphicalDisplay();

  void notify(char cell, int x, int y);

};

#endif


