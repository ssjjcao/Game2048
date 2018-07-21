#ifndef CONTROLLER2048_H
#define CONTROLLER2048_H

#include "Board.h"
#include <ctime>
#include <iostream>

using namespace std;

class Controller2048 {
private:
    Board *board;
    time_t startTime;
    string name;

public:
    Controller2048();

    ~Controller2048();

    void handle();

private:
    void handleHelper();

    void handleInstruction(char instruction);

    void autoRun();

    void autoNextStep();

    void checkGame();

    void printHelp();

    void printRank();

    string format(int time);
};

#endif
