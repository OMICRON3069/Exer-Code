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
    CockSucker(string *src,std::vector<string> &biu);
    bool Debug();  //Maybe is not so bad to use 'cout' to debug....
    string GetLeft() {
        return this->Left;
    }
    string GetRight() {
        return this->Right;
    }
};

class Cunt{

protected:
    string B;
    string First;
    string Follow;

public:
    explicit Cunt(string bb) {
        this->B = std::move(bb);
    }
    bool CalculateFirst(std::vector<CockSucker> &tcs);
    bool CalculateFollow();
    string GetChar() {
        return B;
    }
};

#endif //DING_TESTER_H
