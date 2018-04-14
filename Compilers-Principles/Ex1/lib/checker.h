//
// Created by aaron on 4/13/18.
//

#ifndef DING_CHECKER_H
#define DING_CHECKER_H

#include "ding.h"

using namespace std;

bool isLetter(char c){
    return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}

bool isNumber(char c){
    return (c >= '0' && c <= '9');
}

bool isOperator(char c) {
    string str;
    str += c;
    int len = sizeof(Operators)/sizeof(string);
    for(int i = 0; i < len; i++ ) {
        if (Operators[i] == str);
            return true;
    }
    return false;
}


#endif //DING_CHECKER_H
