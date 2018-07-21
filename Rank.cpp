#include <fstream>
#include "Rank.h"

vector<pair<string, int>> Rank::init() {
    vector<pair<string, int>> rank;
    ifstream file("RankRecord.txt");
    if (file.is_open()) {
        string line; //formation: 473,Smith
        while (getline(file, line)) {
            int splitIndex = line.find(",");
            if (splitIndex != -1) {
                string name = line.substr(splitIndex + 1);
                int time = stoi(line.substr(0, splitIndex));
                pair<string, int> record = make_pair(name, time);
                rank.push_back(record);
            }
        }
    }

    return rank;
};

vector<pair<string, int>> Rank::rankRecord = init();

vector<pair<string, int>> Rank::getRankRecord() {
    return rankRecord;
};

void Rank::store() {
    ofstream output("RankRecord.txt");
    for (int i = 0; i < rankRecord.size(); i++) {
        output << rankRecord[i].second << "," << rankRecord[i].first << endl;
    }
}

void Rank::addRankRecord(string name, int duration) {
    for (int i = 0; i < rankRecord.size(); i++) {
        if (name == rankRecord[i].first) {
            if (duration < rankRecord[i].second) {
                rankRecord[i].second = duration;
                store();
            }
            return;
        }
    }

    pair<string, int> record = make_pair(name, duration);
    for (int i = rankRecord.size() - 1; i >= 0; i--) {
        int time = rankRecord[i].second;
        if (duration >= time) {
            rankRecord.insert(rankRecord.begin() + i + 1, record);
            store();
            return;
        }
    }
    rankRecord.insert(rankRecord.begin(), record);
    store();
}