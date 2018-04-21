//
// Created by omicron3069 on 4/16/2018.
//

#ifndef DING_TESTER_H
#define DING_TESTER_H

#include "Define.cpp"
#include <iostream>
#include <utility>
#include <vector>

class CockSucker{

protected:
    string Left;
    string Right;

public:
    CockSucker(string *src);
    bool Debug();  //Maybe is not so bad to use 'cout' to debug....
};

class Cunt{

protected:
    char B;

public:
    Cunt(char bb) {
        this->B = bb;
    }
    bool CalculateFirst(std::vector<CockSucker> &tcs);
    bool CalculateFollow();
};

#endif //DING_TESTER_H
