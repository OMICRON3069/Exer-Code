//
// Created by aaron on 4/21/18.
//

#ifndef OOO0OOO_CALCULATOR_H
#define OOO0OOO_CALCULATOR_H

#include "Tester.h"
#include "Checker.h"

using namespace std;


bool CalculateFirst(std::vector<CockSucker> &tcs, std::set<char> &FirstSet, char cc) {
    bool SuckerLock = false;
    int count = 0;
    for (auto &it : tcs) {
        string tmp = it.GetRight();
        if (it.GetLeft()[0] == cc) { // Expression match.
            if (!CharacterJudge(tmp[0])) { // If the first one in right side is non end character.
                FirstSet.insert(tmp[0]); //Append this character into FirstSet.
            }
            else {
                for (auto &src : tmp) {
                    if (!CharacterJudge(src)) {
                        FirstSet.insert(src);
                        break;
                    }
                    CalculateFirst(tcs,FirstSet,src);
                    for (auto &ep : FirstSet) {
                        if (ep == '$'){
                            SuckerLock = true;
                            FirstSet.erase('$');
                        }
                    }
                    if (!SuckerLock)
                        break;
                    else {
                        SuckerLock = false;
                        count += 1;
                    }
                }
                if (count == tmp.length()) {
                    FirstSet.insert('$');
                }
            }
        }
    }
}

#endif //OOO0OOO_CALCULATOR_H
