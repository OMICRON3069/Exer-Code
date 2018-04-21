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
    while ((!GrammarBorderDetecter(ite)) && (*ite < count) ){
        *str += Buffer[*ite];
        (*ite)++;
    }

    if (GrammarBorderDetecter(ite)) {
        (*ite)++;
    }

    if (!(*str).empty()){
        CockSucker tmp(str);
        tmp.Debug();
        delete str;
        return tmp;
    }
    delete str;
}

bool StartEngine(int *ite){
    /*
     * Load expression.
     */
    if(LoadSrc("expression.txt"))
        cout << "Load successfully" << "\n";

    /*
     * Resolve expression.
     */
    auto *ThisCockSucker = new vector<CockSucker>;
    while (*ite < count) {
        CockSucker FuckCockSucker = GrammarCreator(ite);
        (*ThisCockSucker).push_back(FuckCockSucker);
    }
    //cout << (*ThisCockSucker).size();
    delete Buffer;
    /*
     * TODO: Load sentence to Buffer here.
     */

    delete ThisCockSucker;
}

#endif //DING_PROCESSER1_H
