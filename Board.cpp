#include <iostream>
#include <vector>
#include "Board.h"

using namespace std;

Board::Board() {
    addRandomTile();
    addRandomTile();
}

Board::Board(const Board &board) {
    this->x = board.x;
    this->z = board.z;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            this->tiles[i][j] = board.tiles[i][j];
        }
    }
}

Board &Board::operator=(const Board &board) {
    if (&board != this) {
        this->x = board.x;
        this->z = board.z;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                this->tiles[i][j] = board.tiles[i][j];
            }
        }
    }
    return *this;
}

void Board::addRandomTile() {
    vector<Tile *> blankTiles;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (tiles[i][j].isTileBlank()) {
                blankTiles.push_back(&tiles[i][j]);
            }
        }
    }

    int size = blankTiles.size();
    if (size == 0) {
        return;
    } else {
        int random = rand() % size;
        double choice = rand() / (double) RAND_MAX;
        int num = choice <= 0.85 ? 2 : 4;
        blankTiles[random]->setNum(num);
    }
}

bool Board::hasBlankTile() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (tiles[i][j].isTileBlank()) {
                return true;
            }
        }
    }
    return false;
}

bool Board::isGameWin() {
    return getMaxNum() >= winNum;
}

bool Board::isGameLose() {
    if (hasBlankTile()) {
        return false;
    } else {
        for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {
                if ((row < boardSize - 1 && tiles[row][col].getNum() == tiles[row + 1][col].getNum())
                    || (col < boardSize - 1 && tiles[row][col].getNum() == tiles[row][col + 1].getNum())) {
                    return false;
                }
            }
        }

        return true;
    }
}

void Board::mergeLeft() {
    bool isAddRandomTile = mergeLeftHelper();
    if (isAddRandomTile) {
        addRandomTile();
    }
}

void Board::mergeRight() {
    bool isAddRandomTile = mergeRightHelper();
    if (isAddRandomTile) {
        addRandomTile();
    }
}

void Board::mergeUp() {
    bool isAddRandomTile = mergeUpHelper();
    if (isAddRandomTile) {
        addRandomTile();
    }
}

void Board::mergeDown() {
    bool isAddRandomTile = mergeDownHelper();
    if (isAddRandomTile) {
        addRandomTile();
    }
}

bool Board::mergeLeftHelper() {
    bool isAddRandomTile = false;

    for (int row = 0; row < boardSize; row++) {
        int count = countTile(row);

        //move
        if (count > 0 && count < boardSize) {
            Tile temp[count];
            int done = 0;
            int col;
            for (col = 0; col < boardSize && done < count; col++) {
                if (!tiles[row][col].isTileBlank()) {
                    temp[done++] = tiles[row][col];
                }
            }

            if (col > count) {
                isAddRandomTile = true;
                for (int i = 0; i < count; i++) {
                    tiles[row][i] = temp[i];
                }

                for (int i = count; i < boardSize; i++) {
                    tiles[row][i].setNum(0);
                }
            }
        }

        //merge
        if (count >= 2) {
            vector<Tile> mergedTiles;
            for (int i = 0; i < count;) {
                int num = tiles[row][i].getNum();
                if (i <= count - 2 && num == tiles[row][i + 1].getNum()) {
                    Tile tileMerged(num + num);
                    mergedTiles.push_back(tileMerged);
                    i = i + 2;
                } else {
                    Tile tile = tiles[row][i];
                    mergedTiles.push_back(tile);
                    i++;
                }
            }

            int size = mergedTiles.size();
            if (size < count) {
                isAddRandomTile = true;
                for (int i = 0; i < size; i++) {
                    tiles[row][i] = mergedTiles[i];
                }

                for (int i = size; i < boardSize; i++) {
                    tiles[row][i].setNum(0);
                }
            }
        }
    }

    return isAddRandomTile;
}

bool Board::mergeRightHelper() {
    rotateBoardBy90();
    rotateBoardBy90();
    bool isAddRandomTile = mergeLeftHelper();
    rotateBoardBy90();
    rotateBoardBy90();
    return isAddRandomTile;
}

bool Board::mergeUpHelper() {
    rotateBoardBy90();
    rotateBoardBy90();
    rotateBoardBy90();
    bool isAddRandomTile = mergeLeftHelper();
    rotateBoardBy90();
    return isAddRandomTile;
}

bool Board::mergeDownHelper() {
    rotateBoardBy90();
    bool isAddRandomTile = mergeLeftHelper();
    rotateBoardBy90();
    rotateBoardBy90();
    rotateBoardBy90();
    return isAddRandomTile;
}

int Board::countTile(int line) {
    int count = 0;
    for (int i = 0; i < boardSize; i++) {
        if (!tiles[line][i].isTileBlank()) {
            count++;
        }
    }
    return count;
}

void Board::rotateBoardBy90() {
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < row; col++) {
            Tile temp = tiles[row][col];
            tiles[row][col] = tiles[col][row];
            tiles[col][row] = temp;
        }
    }

    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize / 2; col++) {
            Tile temp = tiles[row][col];
            tiles[row][col] = tiles[row][boardSize - 1 - col];
            tiles[row][boardSize - 1 - col] = temp;
        }
    }
}

void Board::resetBoard() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            tiles[i][j].setNum(0);
        }
    }
    addRandomTile();
    addRandomTile();
    x = xNum;
    z = zNum;
}

void Board::remove() {
    if (x <= 0) {
        cout << "all x buff has been used up!" << endl;
    } else {
        int min = winNum + 1;
        int count = 0;
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (!tiles[i][j].isTileBlank()) {
                    count++;
                    if (tiles[i][j].getNum() < min) {
                        min = tiles[i][j].getNum();
                    }
                }
            }
        }

        if (count <= 1) {
            cout << "removing this tile is invalid, otherwise nothing is left!" << endl;
        } else {
            vector<Tile *> minTiles;
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (tiles[i][j].getNum() == min) {
                        minTiles.push_back(&tiles[i][j]);
                    }
                }
            }

            int random = rand() % minTiles.size();
            minTiles[random]->setNum(0);
            x--;
        }
    }
}

void Board::reorganize() {
    if (z <= 0) {
        cout << "all z buff has been used up!" << endl;
    } else {
        rotateBoardBy90();
        Tile temp = tiles[0][0];
        tiles[0][0] = tiles[boardSize - 1][boardSize - 1];
        tiles[boardSize - 1][boardSize - 1] = temp;

        temp = tiles[1][0];
        tiles[1][0] = tiles[1][1];
        tiles[1][1] = temp;

        z--;
    }
}

void Board::toSuccess() {
    tiles[0][0].setNum(winNum);
}

int Board::getMaxNum() {
    int max = 0;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (tiles[i][j].getNum() > max) {
                max = tiles[i][j].getNum();
            }
        }
    }
    return max;
}

int Board::evaluate() {
    int weight[boardSize][boardSize];
    for (int i = 0; i < boardSize; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < boardSize; j++) {
                weight[i][j] = 1 << (i * boardSize + j);
            }
        } else {
            for (int j = boardSize - 1; j >= 0; j--) {
                weight[i][j] = 1 << (i * boardSize + boardSize - 1 - j);
            }
        }
    }

    int eval = 0;
    int blankNum = 0;
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (tiles[i][j].isTileBlank()) {
                blankNum++;
            }
            eval += tiles[i][j].getNum() * weight[i][j];
        }
    }

    return eval + getMaxNum() / 2 + blankNum * 2;
}

void Board::printBoard() {
    cout << "-----------------------------------------------------------------" << endl;
    cout << "buff x: " << x << "    buff z: " << z << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < boardSize; i++) {
        cout << "|";
        for (int j = 0; j < boardSize; j++) {
            if (tiles[i][j].isTileBlank()) {
                cout << "\t\t|";
            } else {
                cout << "\t" << tiles[i][j].getNum() << "\t|";
            }
        }
        cout << endl << "-----------------------------------------------------------------" << endl;
    }
}