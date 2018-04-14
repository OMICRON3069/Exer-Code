//
// Created by aaron on 4/13/18.
//

#ifndef DING_ITERATORS_H
#define DING_ITERATORS_H

#include "ding.h"
#include "checker.h"
#include "getter.h"

using namespace std;

bool CheckDing(){
    if (isLetter()){

    }
}


int Split(string* str){
    /*
     * 1 = ' ' or '\n'
     * 2 = Operators
     * 3 = Border
     * 4 = Letter or number and has successfully append into *str.
     */
    if (isLetter() || isNumber()){
        *str += Buffer[ite];
        return 4;
    }
    else {
        int set = BorderDetect();
    }
}

bool StartIteration(){

}

#endif //DING_ITERATORS_H
