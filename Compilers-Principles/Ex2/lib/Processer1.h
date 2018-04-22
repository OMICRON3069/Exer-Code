//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_PROCESSER1_H
#define DING_PROCESSER1_H

#include "Tester.h"
#include "Checker.h"
#include "Calculator.h"

using namespace std;

CockSucker GrammarCreator(int *ite) {
    auto *str = new string;
    while ((!GrammarBorderDetector(ite)) && (*ite < count)) {
        *str += Buffer[*ite];
        (*ite)++;
    }

    if (GrammarBorderDetector(ite)) {
        (*ite)++;
    }

    if (!(*str).empty()) {
        CockSucker tmp(str);
        tmp.Debug();
        delete str;
        return tmp;
    }
    delete str;
}

bool StartEngine(int *ite) {
    /*
     * Load expression.
     */
    if (LoadSrc("expression.txt"))
        cout << "Load expression successfully" << "\n";

    /*
     * Resolve expression.
     */
    vector<CockSucker> ThisCockSucker;
    while (*ite < count)
        ThisCockSucker.push_back(GrammarCreator(ite));
    //cout << ThisCockSucker.size();

    delete Buffer;
    delete ite;

    set<char> CuntNo1; //Non end character.
    set<char> CuntNo2; // End character.

    CuntGenerator(CuntNo1, CuntNo2, ThisCockSucker);



    /*
     * TODO: Load sentence to Buffer here.
     */

}

#endif //DING_PROCESSER1_H
