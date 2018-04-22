//
// Created by aaron on 4/21/18.
//

#ifndef OOO0OOO_CALCULATOR_H
#define OOO0OOO_CALCULATOR_H

#include "Tester.h"
#include "Checker.h"

using namespace std;

bool CalculateFirst(std::vector<CockSucker> &tcs, std::set<char> &FirstSet, char cc) {
    for (auto &it : tcs) {
        string tmp = it.GetRight();
        if (it.GetLeft()[0] == cc) { // Expression match.
            if (!CharacterJudge(tmp[0])) { // If the first one in right side is non end character.
                FirstSet.insert(tmp[0]); //Append this character into FirstSet.
            }
            else {

            }
        }
    }
}

#endif //OOO0OOO_CALCULATOR_H
