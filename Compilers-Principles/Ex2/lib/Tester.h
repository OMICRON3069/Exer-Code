//
// Created by omicron3069 on 4/16/2018.
//

#ifndef DING_TESTER_H
#define DING_TESTER_H

#include "Define.cpp"
#include <iostream>
#include <utility>
#include <vector>
#include <set>

class CockSucker {

protected:
    string Left;
    string Right;

public:
    CockSucker(string *src);

    bool Debug();  //Maybe is not so bad to use 'cout' to debug....
    string GetLeft() {
        return this->Left;
    }

    string GetRight() {
        return this->Right;
    }
};

class Cunt{

public:
    char B;
    explicit Cunt(char b) {
        this->B = b;
    }

    string GetChar() {
        string tmp;
        tmp += B;
        return tmp;
    }

    set<char> FirstSet;
    set<char> FollowSet;


};

#endif //DING_TESTER_H
