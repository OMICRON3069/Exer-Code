//
// Created by aaron on 4/13/18.
//

#ifndef DING_CHECKER_H
#define DING_CHECKER_H

#include "ding.h"

using namespace std;

bool isReservedWord(string *str){
    int len = sizeof(ReservedWord)/sizeof(string);
    for (int i =0 ; i < len ; i++){
        if (ReservedWord[i] == *str)
            return true;
    }
    return false;
}

bool isLetter(){
    return (Buffer[ite] >= 'a' && Buffer[ite] <= 'z' || Buffer[ite] >= 'A' && Buffer[ite] <= 'Z');
}

bool isNumber(){
    return (Buffer[ite] >= '0' && Buffer[ite] <= '9');
}


int BorderDetect(){
    /*
     * BorderDetect function return value meaning.
     * 1 = ' ' or '\n'
     * 2 = Operators
     * 3 = Border
     */
    string str;
    str += Buffer[ite];
    int lenB = sizeof(Border)/ sizeof(string);
    int lenO = sizeof(Operators)/ sizeof(string);
    if (Buffer[ite] != 32 || Buffer[ite] != 10) {
        for(int i = 0; i < lenO; i++ ) {
            if (Operators[i] == str)
                return 2;
        }
        for(int i = 0; i < lenB; i++ ) {
            if (Border[i] == str)
                return 3;
        }
    }
    return 1;
}

#endif //DING_CHECKER_H
