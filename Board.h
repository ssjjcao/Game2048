#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"

class Board {
private:
    static const int boardSize = 4;
    static const int winNum = 2048;
    static const int xNum = 100;
    static const int zNum = 10;
    int x = xNum; //times left to remove the smallest
    int z = zNum; //times left to reorganize the tiles
    Tile tiles[boardSize][boardSize];

public:
    Board();

    Board(const Board &board);

    Board &operator=(const Board &board);

    void addRandomTile();

    void mergeLeft();

    void mergeRight();

    void mergeUp();

    void mergeDown();

    bool mergeLeftHelper();

    bool mergeRightHelper();

    bool mergeUpHelper();

    bool mergeDownHelper();

    void resetBoard();

    void remove();

    void reorganize();

    void toSuccess();

    bool isGameWin();

    bool isGameLose();

    int evaluate();

    void printBoard();

private:
    bool hasBlankTile();

    int getMaxNum();

    int countTile(int line);

    void rotateBoardBy90();
};

#endif
