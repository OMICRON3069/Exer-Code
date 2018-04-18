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
    bool LeftLock = true;
    for (char &it : (*src)) {
        //Check
        //cout << "Test Doc is " << it << "\n";
        if(it == '-' || it == '>'){
            LeftLock = false;
        }
        else if (LeftLock){
            this->Left += it;
        }
        else if (!LeftLock){
            this->Right += it;
        }
    }

}

bool CockSucker::Debug() {
    cout << "Debug info " << "\n";
    cout << "Left: " << this->Left << " Right: " << this->Right <<"\n";
}

#endif //DING_CHECKER_H
