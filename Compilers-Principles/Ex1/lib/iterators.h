//
// Created by aaron on 4/13/18.
//

#ifndef DING_ITERATORS_H
#define DING_ITERATORS_H

#include "ding.h"
#include "checker.h"
#include "getter.h"

using namespace std;


int Split(string *str){
    /*
     * 1 = ' ' or '\n'
     * 2 = Operators
     * 3 = Border
     * 4 = Letter or number has successfully append into *str.
     */
    if (isLetter() || isNumber()){
        if (isLetter())
            NumLock = false;
        *str += Buffer[ite];
        lock = true;
        return 4;
    }
    else return BorderDetect();
}

bool CheckDing(){
    auto *str = new string();
    NumLock = true;
    int tmp = Split(str);
    while (tmp == 4){
        ite++;
        tmp = Split(str);
    }
    if (lock){
        //cout << *str << "\n";
        if (isReservedWord(str)){
            int num = GetReservedWord(str);
            cout << "ReservedWord:\t" << ReservedWord[num] << "\n";
        }
        else {
            if (NumLock){
                cout << "Number:\t" << *str << "\n";
            }
            else cout << "Ident:\t" << *str << "\n";
        }

        lock = false;
    }
    if (tmp == 2){
        int num = GetOperator();
        cout<< OperatorsKey[num] <<":\t"<<  Operators[num] <<"\n";
        ite++;
        delete str;
        return true;
    }
    else if (tmp == 3){
        int num = GetBorder();
        cout<< BorderKey[num] <<":\t"<<  Border[num] <<"\n";
        ite++;
        delete str;
        return true;
    }
    else if (tmp == 1){
        ite++;
        delete str;
        return true;
    }
}

bool StartIteration(){
    if (CheckDing()){
        if (ite == (count)) return true;
        else StartIteration();
    }
    else return false;
}

#endif //DING_ITERATORS_H
