#ifndef AUTO_H
#define AUTO_H

#include "Board.h"

enum direction {
    UP, DOWN, LEFT, RIGHT
};

class Auto {
public:
    static direction getNextStep(const Board &board);

private:
    static int search(const Board &board, int depth);
};

#endif
