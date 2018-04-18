//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_CHECKER_H
#define DING_CHECKER_H

#include "Tester.h"
using namespace std;

bool IsEndCharacter(int *tmp){
    return !(Buffer[*tmp] >= 'A' || Buffer[*tmp] <= 'Z');
}

bool GrammarBorderDetecter(int *ite){
    //return Buffer[*ite] != '\n';
    if (Buffer[*ite] != '\n'){
        return false;
    }
    else return true;
}

CockSucker::CockSucker(string *src) {
    for (char &it : (*src)) {
        cout << "Test Doc is" << it << "\n";
    }

}

#endif //DING_CHECKER_H
