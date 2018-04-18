//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_PROCESSER1_H
#define DING_PROCESSER1_H

#include "Tester.h"
#include "Checker.h"
#include <vector>

using namespace std;

CockSucker GrammarCreator(int *ite){
    auto *str = new string;
    while (!GrammarBorderDetecter(ite)){
        *str += Buffer[*ite];
        (*ite)++;
    }

    if (!(*str).empty()){
        CockSucker tmp(str);
        tmp.Debug();
        return tmp;
    }
}

bool StartEngine(int *ite){
    auto *ThisCockSucker = new vector<CockSucker>;
    CockSucker FuckCockSucker = GrammarCreator(ite);
    (*ThisCockSucker).push_back(FuckCockSucker);

}

#endif //DING_PROCESSER1_H
