#ifndef RANK_H
#define RANK_H

#include <vector>

using namespace std;

class Rank {
private:
    static vector<pair<string, int>> rankRecord;

    static vector<pair<string, int>> init();

    static void store();

public:
    static vector<pair<string, int>> getRankRecord();

    static void addRankRecord(string name, int duration);
};

#endif
