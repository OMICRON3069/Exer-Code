//
// Created by aaron on 4/13/18.
//

#ifndef DING_GETTER_H
#define DING_GETTER_H

#include "ding.h"

using namespace std;

int GetOperator(string OpName){
    int len = sizeof(Operators)/ sizeof(string);
    for (int i = 0; i < len; i++) {
        if (Operators[i] == OpName) {
            return i;
        }
    }
    return 114514;
}


#endif //DING_GETTER_H
