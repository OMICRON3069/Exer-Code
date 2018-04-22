//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_CHECKER_H
#define DING_CHECKER_H

#include "Tester.h"

using namespace std;

bool CharacterJudge(char cc) {
    return cc >= 'A' && cc <= 'Z';
}


bool CuntGenerator(std::set<char> &c1, std::set<char> &c2, std::vector<CockSucker> &tcs) {
    string *tmp;
    for (auto &it : tcs) {
        tmp = new string;
        *tmp = it.GetLeft();
        c1.insert(*((*tmp).begin()));
        delete tmp;

        tmp = new string;
        *tmp = it.GetRight();
        for (int i = 0; i < (*tmp).size(); i++) {
            if (!CharacterJudge(*((*tmp).begin() + i)))
                c2.insert(*((*tmp).begin() + i));
        }
        delete tmp;
    }
    c2.insert('#');
}

bool GrammarBorderDetector(int *ite) {
    //return Buffer[*ite] != '\n';
    if (Buffer[*ite] != '\n') {
        return false;
    } else if (Buffer[*ite] == 0)
        return false;
    else return true;
}

CockSucker::CockSucker(string *src) {
    bool LeftLock = true;
    for (auto &it : (*src)) {
        //Check
        //cout << "Test Doc is " << it << "\n";
        if (it == '-' || it == '>') {
            LeftLock = false;
        } else if (LeftLock) {
            this->Left += it;
        } else if (!LeftLock) {
            this->Right += it;
        }
    }

}

bool CockSucker::Debug() {
    cout << "Debug info " << "\n";
    cout << "Left: " << this->Left << " Right: " << this->Right << "\n";
}

#endif //DING_CHECKER_H
