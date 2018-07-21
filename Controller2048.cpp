#include "Controller2048.h"
#include <iostream>
#include <conio.h>
#include "Rank.h"
#include "Auto.h"

using namespace std;

Controller2048::Controller2048() {
    board = new Board();
}

Controller2048::~Controller2048() {
    delete board;
}

void Controller2048::printHelp() {
    cout << "Hello, " << name << "! Instructions are here:" << endl
         << "press 'w','a','s','d' to move or merge the tiles; press 'r' to restart a new game;" << endl
         << "press 'x' to remove a smallest tile randomly; press 'z' to reorganize the tiles in the board;" << endl
         << "press 'v', and you can success directly;" << endl
         << "press 'c' to play the game automatically; press 'q' to quit;" << endl
         << "*** You only have 10 seconds to think about your next instruction ***" << endl
         << "*** A random tile will be added if time is out ***" << endl;
}

void Controller2048::printRank() {
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Rank:" << endl;
    vector<pair<string, int>> rankRecord = Rank::getRankRecord();
    int size = rankRecord.size();
    if (size == 0) {
        cout << "Nobody has pass 2048, to be the first!" << endl;
    } else {
        for (int i = 0; i < size; i++) {
            string name = rankRecord[i].first;
            int time = rankRecord[i].second;
            cout << name << "\t" << format(time) << endl;
        }
    }
}

string Controller2048::format(int time) {
    string result;
    if (time >= 3600) {
        result += to_string(time / 3600);
        result += "h";
        time = time % 3600;
    }

    if (time >= 60) {
        result += to_string(time / 60);
        result += "min";
        time = time % 60;
    }

    if (time >= 0) {
        result += to_string(time);
        result += "s";
    }

    return result;
}

void Controller2048::handle() {
    cout << "Welcome to 2048!" << endl << "please input your user name:" << endl;
    string name;
    getline(cin, name);
    this->name = name;
    cout << endl;

    printHelp();
    printRank();
    board->printBoard();
    this->startTime = time(nullptr);
    while (true) {
        handleHelper();
    }
}

void Controller2048::handleHelper() {
    time_t limit = time(nullptr) + 10;
    while (time(nullptr) <= limit) {
        if (kbhit()) {
            handleInstruction((char) getch());
            return;
        }
    }
    cout << endl << "Time is out!" << endl;
    board->addRandomTile();
    board->printBoard();
    checkGame();
}

void Controller2048::handleInstruction(char instruction) {
    if (instruction == 'w') {
        board->mergeUp();
        cout << endl << "instruction: w" << endl;
        board->printBoard();
        checkGame();
    } else if (instruction == 'a') {
        board->mergeLeft();
        cout << endl << "instruction: a" << endl;
        board->printBoard();
        checkGame();
    } else if (instruction == 's') {
        board->mergeDown();
        cout << endl << "instruction: s" << endl;
        board->printBoard();
        checkGame();
    } else if (instruction == 'd') {
        board->mergeRight();
        cout << endl << "instruction: d" << endl;
        board->printBoard();
        checkGame();
    } else if (instruction == 'v') {
        board->toSuccess();
        cout << endl << "instruction: v" << endl;
        board->printBoard();
        checkGame();
    } else if (instruction == 'r') {
        board->resetBoard();
        startTime = time(nullptr);
        cout << endl << "instruction: r" << endl;
        board->printBoard();
    } else if (instruction == 'x') {
        board->remove();
        cout << endl << "instruction: x" << endl;
        board->printBoard();
    } else if (instruction == 'z') {
        board->reorganize();
        cout << endl << "instruction: z" << endl;
        board->printBoard();
        checkGame();
    } else if (instruction == 'c') {
        autoRun();
    } else if (instruction == 'q') {
        delete board;
        exit(0);
    } else {
        cout << "wrong instruction!" << endl;
    }
}

void Controller2048::autoRun() {
    while (true) {
        bool isWin = board->isGameWin();
        bool isLose = board->isGameLose();

        if (isWin || isLose) {
            if (isWin) {
                int duration = time(nullptr) - startTime;
                Rank::addRankRecord(name, duration);
                cout << "2048 appears!" << endl;
                printRank();
                cout << "'r' to restart, 'q' to quit." << endl;
            } else {
                cout << "Sorry, we fail to help you play 2048. 'r' to restart, 'q' to quit." << endl;
            }

            while (true) {
                if (kbhit()) {
                    char instruction = getch();
                    if (instruction == 'r') {
                        board->resetBoard();
                        startTime = time(nullptr);
                        cout << endl << "instruction: r" << endl;
                        board->printBoard();
                        break;
                    } else if (instruction == 'q') {
                        delete board;
                        exit(0);
                    } else {
                        cout << "wrong instruction! hint:'r' to restart, 'q' to quit." << endl;
                    }
                }
            }

            break;
        } else {
            autoNextStep();
        }
    }
}

void Controller2048::autoNextStep() {
    direction nextStep = Auto::getNextStep(*board);
    switch (nextStep) {
        case UP:
            board->mergeUp();
            cout << endl << "instruction: w" << endl;
            board->printBoard();
            break;
        case DOWN:
            board->mergeDown();
            cout << endl << "instruction: s" << endl;
            board->printBoard();
            break;
        case LEFT:
            board->mergeLeft();
            cout << endl << "instruction: a" << endl;
            board->printBoard();
            break;
        case RIGHT:
            board->mergeRight();
            cout << endl << "instruction: d" << endl;
            board->printBoard();
            break;
    }
}

void Controller2048::checkGame() {
    bool isWin = board->isGameWin();
    bool isLose = board->isGameLose();

    if (isWin || isLose) {
        if (isWin) {
            int duration = time(nullptr) - startTime;
            Rank::addRankRecord(name, duration);
            cout << "Congratulations, you win!" << endl;
            printRank();
            cout << "'r' to restart, 'q' to quit." << endl;
        } else {
            cout << "Game over, you fail. 'r' to restart, 'q' to quit." << endl;
        }

        while (true) {
            if (kbhit()) {
                char instruction = getch();
                if (instruction == 'r') {
                    board->resetBoard();
                    startTime = time(nullptr);
                    cout << endl << "instruction: r" << endl;
                    board->printBoard();
                    break;
                } else if (instruction == 'q') {
                    delete board;
                    exit(0);
                } else {
                    cout << "wrong instruction! hint:'r' to restart, 'q' to quit." << endl;
                }
            }
        }
    }
}