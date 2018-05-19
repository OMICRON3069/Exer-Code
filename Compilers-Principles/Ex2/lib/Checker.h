//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_CHECKER_H
#define DING_CHECKER_H

#include "Tester.h"

using namespace std;

bool CharacterJudge(char cc) {//non terminate cha return true
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
    return true;
}

bool GrammarBorderDetector(int *ite) {
    //return Buffer[*ite] != '\n';
    if (Buffer[*ite] != '\n') {
        return false;
    }
    else if (Buffer[*ite] == 0)
        return false;
    else return true;
}

CockSucker::CockSucker(string *src) {
    bool LeftLock = true;
    for (auto &it : (*src)) {
        if (it == '-' || it == '>') {
            LeftLock = false;
        }
        else if (LeftLock) {
            this->Left += it;
            if (fLock) {
                fLock =false;
                f = it;
            }
        }
        else if (!LeftLock) {
            this->Right += it;
        }
    }

}

bool CockSucker::Debug() {
    cout << "Left: " << this->Left << " Right: " << this->Right << "\n";
    return true;
}

Cunt &GetCunt(char d, std::vector<Cunt> &CuntCluster) {
    for (auto &it : CuntCluster) {
        if (it.B == d) {
            return it;
        }
    }
    cout << "error while get Cunt\n";
    exit(0);
}

int GetCuntID(char b,std::set<char> &CuntN) {
    int i=0;
    for (auto &it : CuntN) {
        if (b == it) {
            return i;
        }
        i++;
    }
    cout << "CuntID Not Found\n";
    cout <<b;
    exit(0);
}

CockSucker &GetCockSuckerByID(int d,std::vector<CockSucker> &tcs) {
    int i=0;
    for (auto &it : tcs) {
        if (i == d) {
            return it;
        }
        i++;
    }
    cout << "CockSucker ID Not Found\n";
    exit(0);
}

int GetTableMapValue (char l, char r, std::set<char> n1, std::set<char> n2) {
    return TableMap[GetCuntID(l,n1)][GetCuntID(r,n2)];
}

#endif //DING_CHECKER_H
