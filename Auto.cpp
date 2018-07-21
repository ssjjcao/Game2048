#include "Auto.h"

int Auto::search(const Board &board, int depth) {
    depth--;
    Board boardCopy = board;
    boardCopy.addRandomTile();

    if (boardCopy.isGameLose()) {
        return -100000000;
    } else if (boardCopy.isGameWin()) {
        return 0x7fffffff;
    } else if (depth == 0) {
        return boardCopy.evaluate();
    } else {
        int evalUp = 1;
        int evalDown = 0;
        int evalLeft = 3;
        int evalRight = 2;

        Board boardUp = boardCopy;
        Board boardDown = boardCopy;
        Board boardLeft = boardCopy;
        Board boardRight = boardCopy;

        if (boardUp.mergeUpHelper()) {
            evalUp = search(boardUp, depth);
        }

        if (boardDown.mergeDownHelper()) {
            evalDown = search(boardDown, depth);
        }

        if (boardLeft.mergeLeftHelper()) {
            evalLeft = search(boardLeft, depth);
        }

        if (boardRight.mergeRightHelper()) {
            evalRight = search(boardRight, depth);
        }

        if (evalUp >= evalDown && evalUp >= evalLeft && evalUp >= evalRight) {
            return evalUp;
        } else if (evalDown >= evalLeft && evalDown >= evalRight) {
            return evalDown;
        } else if (evalLeft >= evalRight) {
            return evalLeft;
        } else {
            return evalRight;
        }
    }
}

direction Auto::getNextStep(const Board &board) {
    int evalUp = 0;
    int evalDown = 1;
    int evalLeft = 2;
    int evalRight = 3;

    Board boardUp = board;
    Board boardDown = board;
    Board boardLeft = board;
    Board boardRight = board;

    if (boardUp.mergeUpHelper()) {
        evalUp = search(boardUp, 9);
    }

    if (boardDown.mergeDownHelper()) {
        evalDown = search(boardDown, 9);
    }

    if (boardLeft.mergeLeftHelper()) {
        evalLeft = search(boardLeft, 9);
    }

    if (boardRight.mergeRightHelper()) {
        evalRight = search(boardRight, 9);
    }

    if (evalUp >= evalDown && evalUp >= evalLeft && evalUp >= evalRight) {
        return UP;
    } else if (evalDown >= evalLeft && evalDown >= evalRight) {
        return DOWN;
    } else if (evalLeft >= evalRight) {
        return LEFT;
    } else {
        return RIGHT;
    }
}