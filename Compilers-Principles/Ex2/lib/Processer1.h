//
// Created by omicron3069 on 4/18/2018.
//

#ifndef DING_PROCESSER1_H
#define DING_PROCESSER1_H

#include "Tester.h"
#include "Checker.h"
#include "Calculator.h"
#include "Analyzer.h"

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
        cout << "Load expression successfully\n\n";

    /*
     * Resolve expression.
     */
    vector<CockSucker> ThisCockSucker;
    while (*ite < count)
        ThisCockSucker.push_back(GrammarCreator(ite));
    //cout << ThisCockSucker.size();

    delete Buffer;
    delete ite;

    set<char> CuntNo1; //Non-Terminal character. eg:'E'.
    set<char> CuntNo2; // Terminal character. eg:'e'.

    CuntGenerator(CuntNo1, CuntNo2, ThisCockSucker);

    vector<Cunt> CuntCluster;

    if (StartFirst(CuntNo1, CuntCluster, ThisCockSucker))
        cout << "First set calculated successfully\n\n";

    if (StartFollow(CuntCluster, ThisCockSucker))
        cout << "Follow set calculated successfully\n\n";

    if (TableGen(CuntCluster,ThisCockSucker,CuntNo1,CuntNo2))
        cout << "Predict table calculated successfully\n\n";

    /*
     * TODO: Load sentence to Buffer here.
     */

    if (LoadSrc("sentence.txt"))
        cout << "Load sentence successfully\n\n";

    vector<char> Polar;

    if (AnalyzeSentence(ite,Polar,ThisCockSucker,CuntCluster,CuntNo1,CuntNo2))
        cout << "Main task finished!!\n\n";

    return true;
}

#endif //DING_PROCESSER1_H
